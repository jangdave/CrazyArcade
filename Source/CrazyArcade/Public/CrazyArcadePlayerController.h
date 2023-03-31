// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CrazyArcadePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API ACrazyArcadePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Camera")
	TSubclassOf<class ACameraActor> CameraFactory;
	UPROPERTY(EditAnywhere, Category = "Camera")
	class AMainCamera* MainCamera;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInGameWidget> InGameWidgetFactory;
	UPROPERTY()
	class UInGameWidget* InGameWidget;
};
