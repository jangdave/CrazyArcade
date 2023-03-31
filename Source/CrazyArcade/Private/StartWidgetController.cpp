// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidgetController.h"
#include "CrazyGameInstance.h"
#include "LobbyWidget.h"
#include "LobbyPlayerWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void AStartWidgetController::BeginPlay()
{
	Super::BeginPlay();

	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());

	if(lobbyWidget != nullptr && IsLocalController())
	{
		lobbyWid = CreateWidget<ULobbyWidget>(this, lobbyWidget);

		lobbyWid->AddToViewport();

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);

		ServerPlayWidget();
	}

}

void AStartWidgetController::ServerPlayWidget_Implementation()
{
	MulticastPlayWidget();
}

void AStartWidgetController::MulticastPlayWidget_Implementation()
{
	auto playerWid = CreateWidget<ULobbyPlayerWidget>(this, playerWidget);

	if (playerWid != nullptr)
	{
		playerWid->text_PlayerName->SetText(FText::FromName(gameInstance->GetName()));

		lobbyWid->horizonBox_PlayerList1->AddChild(playerWid);
	}
}