// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameFramework/GameStateBase.h"
#include "ShowResultGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API AShowResultGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AShowResultGameStateBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


public:

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UWinWidget> WinWidgetFactory;
	UPROPERTY()
	class UWinWidget* WinWidget;

	UPROPERTY()
	int32 PlayersNum;

	UFUNCTION()
	void SetResult();


private:
	class ACrazyArcadePlayer* Player;
};
