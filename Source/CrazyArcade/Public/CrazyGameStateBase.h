// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CrazyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API ACrazyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(Replicated)
	int32 checkCount;
};
