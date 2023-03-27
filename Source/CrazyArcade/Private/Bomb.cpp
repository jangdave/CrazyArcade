// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"

#include "CrazyArcadePlayer.h"
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

	BombParticlesVertical = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Bomb Particles Vertical"));
	BombParticlesVertical->SetupAttachment(RootComponent);

	BombCollisionVertical = CreateDefaultSubobject<UBoxComponent>(TEXT("Bomb Collision Vertical"));
	BombCollisionVertical->SetupAttachment(BombParticlesVertical);
	BombCollisionVertical->SetBoxExtent(FVector(40.f, 150.f, 45.f));

	BombParticlesHorizontal = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Bomb Particles Horizontal"));
	BombParticlesHorizontal->SetupAttachment(RootComponent);

	BombCollisionHorizontal = CreateDefaultSubobject<UBoxComponent>(TEXT("Bomb Collision Horizontal"));
	BombCollisionHorizontal->SetupAttachment(BombParticlesHorizontal);
	BombCollisionHorizontal->SetBoxExtent(FVector(40.f, 150.f, 45.f));

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
	BombParticlesVertical->Activate(true);
	BombCollisionHorizontal->Activate(true);
}

void ABomb::OnBombPopBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Stun"));

	auto player = Cast<ACrazyArcadePlayer>(OtherActor);
	if(player == nullptr)
	{
		return;
	}

	player->SetActorLocation(GetActorLocation());
	player->SpawnStunBomb();
}
