// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyArcadeGameMode.h"
#include "CrazyArcadeCharacter.h"
#include "EngineUtils.h"
#include "MainCamera.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "InGameWidget.h"
#include "GameFramework/PlayerStart.h"

ACrazyArcadeGameMode::ACrazyArcadeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

AActor* ACrazyArcadeGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	Super::ChoosePlayerStart_Implementation(Player);

	// 월드 안에 있는 APlayerStart 액터들을 가져온다.
	for (TActorIterator<APlayerStart> itr(GetWorld()); itr; ++itr)
	{
		APlayerStart* playerStart = *itr;
		if (playerStart->PlayerStartTag != FName("Spawned"))
		{
			// 반환될 APlayerStart 액터의 태그"Spawned"를 추가한다.
			playerStart->PlayerStartTag = FName("Spawned");
			return playerStart;
		}
	}

	return nullptr;
}