// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CrazyArcadeGameMode.generated.h"

UCLASS(minimalapi)
class ACrazyArcadeGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ACrazyArcadeGameMode();

	UPROPERTY(EditAnywhere, Category="Camera")
	TSubclassOf<class ACameraActor> CameraFactory;
	UPROPERTY(EditAnywhere, Category = "Camera")
	class AMainCamera* MainCamera;
};



