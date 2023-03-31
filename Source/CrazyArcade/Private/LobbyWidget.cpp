// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_BackLobby->OnClicked.AddDynamic(this, &ULobbyWidget::BackLobby);
	btn_StartGame->OnClicked.AddDynamic(this, &ULobbyWidget::StartLevel);

	// 색상 선택
	btn_Blue->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorBlue);
	btn_Green->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorGreen);
	btn_Yellow->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorYellow);
	btn_Red->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorRed);
	btn_Pink->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorPink);
	btn_Orange->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorOrange);
	btn_Indigo->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorIndigo);
	btn_Black->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorBlack);
}

void ULobbyWidget::StartLevel()
{
	GetWorld()->ServerTravel("/Game/Maps/MainLevel?Listen");
}

void ULobbyWidget::BackLobby()
{

}

void ULobbyWidget::SetColorBlue()
{

}

void ULobbyWidget::SetColorGreen()
{

}

void ULobbyWidget::SetColorYellow()
{

}

void ULobbyWidget::SetColorRed()
{

}

void ULobbyWidget::SetColorPink()
{

}

void ULobbyWidget::SetColorOrange()
{

}

void ULobbyWidget::SetColorIndigo()
{

}

void ULobbyWidget::SetColorBlack()
{

}
