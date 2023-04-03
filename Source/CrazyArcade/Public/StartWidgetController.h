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

	UFUNCTION(Server, Unreliable)
	void ServerPlayWidget();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPlayWidget();

	class UCrazyGameInstance* gameInstance;

	UFUNCTION()
	void SetColor();
	
	UPROPERTY(Replicated)
	FVector color;
};
