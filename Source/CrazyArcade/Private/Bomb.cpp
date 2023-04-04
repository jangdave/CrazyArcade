// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"

#include "CrazyArcadePlayer.h"
#include "DestroyBox.h"
#include "FixBox.h"
#include "GridTile.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(52.f);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -50.f));

	BombCollisionVertical = CreateDefaultSubobject<UBoxComponent>(TEXT("Bomb Collision Vertical"));
	BombCollisionVertical->SetupAttachment(RootComponent);
	BombCollisionVertical->SetBoxExtent(FVector(40.f, 140.f, 45.f));
	BombCollisionVertical->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BombParticlesVertical = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Bomb Particles Vertical"));
	BombParticlesVertical->SetupAttachment(BombCollisionVertical);

	BombCollisionHorizontal = CreateDefaultSubobject<UBoxComponent>(TEXT("Bomb Collision Horizontal"));
	BombCollisionHorizontal->SetupAttachment(RootComponent);
	BombCollisionHorizontal->SetBoxExtent(FVector(40.f, 140.f, 45.f));
	BombCollisionHorizontal->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BombParticlesHorizontal = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Bomb Particles Horizontal"));
	BombParticlesHorizontal->SetupAttachment(BombCollisionHorizontal);
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	BombCollisionVertical->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnBombPopBeginOverlap);
	BombCollisionHorizontal->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnBombPopBeginOverlap);

	FTimerHandle BombHandle;
	GetWorldTimerManager().SetTimer(BombHandle, FTimerDelegate::CreateLambda([this]()->void
		{
			Pop();
			Destroy();
		}
	), 3.f, false, 3.f);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::Pop()
{
	BombParticlesVertical->ActivateSystem(true);
	BombParticlesHorizontal->ActivateSystem(true);


	BombCollisionVertical->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BombCollisionHorizontal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABomb::OnBombPopBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<ACrazyArcadePlayer>(OtherActor);
	auto destroyBox = Cast<ADestroyBox>(OtherActor);
	auto fixBox = Cast<AFixBox>(OtherActor);

	if(player != nullptr)
	{
		float dist = 0.f;
		FVector stunLocation = player->FindNearstTile(player->GetActorLocation(), player->GridTiles, dist)->GetActorLocation();
		player->SetActorLocation(stunLocation);
		player->SpawnStunBomb();
	}

	if(destroyBox != nullptr)
	{
		destroyBox->DestroyBox();
	}

	if(fixBox != nullptr)
	{
		
	}
}
