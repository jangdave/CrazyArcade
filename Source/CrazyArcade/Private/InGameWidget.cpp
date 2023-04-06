// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"

#include "CrazyArcadePlayer.h"
#include "StartWidgetController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void UInGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	playerNames = { Text_Player0 , Text_Player1, Text_Player2, Text_Player3, Text_Player4, Text_Player5, Text_Player6, Text_Player7 };

	player = Cast<ACrazyArcadePlayer>(GetOwningPlayerPawn());

	btn_Quit->OnClicked.AddDynamic(this, &UInGameWidget::QuitGame);
}

void UInGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetName();
}

void UInGameWidget::SetName()
{
	auto players = GetWorld()->GetGameState()->PlayerArray;

	for (int i = 0; i < players.Num(); i++)
	{
		playerNames[i]->SetText(FText::FromString(players[i]->GetPlayerName()));
	}
}

void UInGameWidget::QuitGame()
{
	player->DestroyGame();
}
