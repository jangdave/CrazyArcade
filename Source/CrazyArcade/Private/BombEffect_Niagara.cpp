// Fill out your copyright notice in the Description page of Project Settings.


#include "BombEffect_Niagara.h"

#include "CrazyArcadePlayer.h"
#include "DestroyBox.h"
#include "FixBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

UBombEffect_Niagara::UBombEffect_Niagara()
{
	bWantsInitializeComponent = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
}

void UBombEffect_Niagara::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &UBombEffect_Niagara::OnBombPopBeginOverlap);
}

void UBombEffect_Niagara::OnBombPopBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<ACrazyArcadePlayer>(OtherActor);
	auto destroyBox = Cast<ADestroyBox>(OtherActor);
	auto fixBox = Cast<AFixBox>(OtherActor);

	if(player != nullptr)
	{
		// player->Stun();
	}

	if(destroyBox != nullptr)
	{
		destroyBox->Destroy();
	}
}
