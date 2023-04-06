// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ShowResultGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API AShowResultGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UWinWidget> WinWidgetFactory;
	UPROPERTY()
	class UWinWidget* WinWidget;


	UFUNCTION()
	void SetResult();
};
