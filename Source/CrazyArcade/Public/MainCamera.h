// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MainCamera.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API AMainCamera : public ACameraActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Unreliable)
	void ServerSetMainCamera();
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSetMainCamera();

	UFUNCTION()
	void SetMainCamera();
};
