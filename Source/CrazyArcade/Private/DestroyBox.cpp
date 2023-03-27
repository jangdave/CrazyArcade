// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestroyBox::ADestroyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ADestroyBox::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADestroyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyBox::DestroyBox()
{
	this->Destroy();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), destroyEmitter, GetActorLocation());
}

