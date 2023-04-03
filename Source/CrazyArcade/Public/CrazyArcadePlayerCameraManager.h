// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CrazyArcadePlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API ACrazyArcadePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
