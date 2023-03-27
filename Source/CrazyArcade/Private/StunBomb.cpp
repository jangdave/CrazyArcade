// Fill out your copyright notice in the Description page of Project Settings.


#include "StunBomb.h"

// Sets default values
AStunBomb::AStunBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);
}

// Called when the game starts or when spawned
void AStunBomb::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle StunHandle;
	GetWorldTimerManager().SetTimer(StunHandle, FTimerDelegate::CreateLambda([this]()->void
		{
			Destroy();
		}
	), 3.f, false, 3.f);
}

// Called every frame
void AStunBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

