// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyArcadeGameMode.h"
#include "CrazyArcadeCharacter.h"
#include "MainCamera.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"

ACrazyArcadeGameMode::ACrazyArcadeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ACrazyArcadeGameMode::BeginPlay()
{
	Super::BeginPlay();

	MainCamera = Cast<AMainCamera>(GetWorld()->SpawnActor<ACameraActor>(CameraFactory));
	MainCamera->SetActorLocationAndRotation(FVector(1500.f, 1750.f, 2500.f), FRotator(-90.f, 0.f, 0.f));

	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(PlayerController)
	{
		PlayerController->SetViewTarget(MainCamera);
	}
}
