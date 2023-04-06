// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CrazyLobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API ACrazyLobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(Replicated)
	FLinearColor SetButtonColor;
	
	UFUNCTION()
	void ButtonColor(FVector color);
};
