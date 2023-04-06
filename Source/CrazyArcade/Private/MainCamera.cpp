// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"

#include "CrazyArcadePlayer.h"
#include "CrazyArcadePlayerController.h"

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	SetMainCamera();
}

void AMainCamera::SetMainCamera()
{
	auto playerController = Cast <ACrazyArcadePlayerController>(GetWorld()->GetFirstPlayerController());

	if (playerController != nullptr && playerController->IsLocalController())
	{
		playerController->SetViewTarget(this);
		UE_LOG(LogTemp, Warning, TEXT("Main Camera Setviewed"));
	}
}

void AMainCamera::MulticastSetMainCamera_Implementation()
{
	SetMainCamera();
}

void AMainCamera::ServerSetMainCamera_Implementation()
{

	MulticastSetMainCamera();
}
