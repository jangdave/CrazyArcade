// Fill out your copyright notice in the Description page of Project Settings.


#include "FixBox.h"
#include "Components/BoxComponent.h"

// Sets default values
AFixBox::AFixBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void AFixBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFixBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

