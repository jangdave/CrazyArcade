// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StartWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API AStartWidgetController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	AStartWidgetController();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ULobbyWidget> lobbyWidget;

	UPROPERTY()
	class ULobbyWidget* lobbyWid;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ULobbyPlayerWidget> playerWidget;
	
	class UCrazyGameInstance* gameInstance;
	
	UFUNCTION()
	void SetColor();

	UFUNCTION(Server, Unreliable)
	void SetServerColor();

	UFUNCTION(NetMulticast, Unreliable)
	void SetMulticastColor();

	UPROPERTY(ReplicatedUsing = SetMulticastColor)
	FVector color;

	class ACrazyArcadePlayer* owner;
};
