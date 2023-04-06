// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidgetController.h"
#include "CrazyArcadePlayer.h"
#include "CrazyGameInstance.h"
#include "LobbyWidget.h"
#include "Components/HorizontalBox.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AStartWidgetController::AStartWidgetController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStartWidgetController::BeginPlay()
{
	Super::BeginPlay();

	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());

	if(lobbyWidget != nullptr && IsLocalController())
	{
		lobbyWid = CreateWidget<ULobbyWidget>(GetWorld(), lobbyWidget);

		lobbyWid->AddToViewport();

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	}
}

void AStartWidgetController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AStartWidgetController::SetColor()
{
	color = lobbyWid->SetColor();

	gameInstance->setMatColor = color;
}