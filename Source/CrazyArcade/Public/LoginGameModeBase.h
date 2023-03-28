// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API ALoginGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoginGameModeBase();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameStartWidget> gameStartWidget;

	UPROPERTY()
	class UGameStartWidget* gameStart_UI;
};
