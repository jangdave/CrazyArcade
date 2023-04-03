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

	setColor = FVector(1, 1, 1);
}

void ULobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

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
	setColor = FVector(0, 0, 1);
}

void ULobbyWidget::SetColorGreen()
{
	setColor = FVector(0, 1, 0);

}

void ULobbyWidget::SetColorYellow()
{
	setColor = FVector(1, 1, 0);
}

void ULobbyWidget::SetColorRed()
{
	setColor = FVector(1, 0, 0);
}

void ULobbyWidget::SetColorPink()
{
	setColor = FVector(1, 0, 1);
}

void ULobbyWidget::SetColorOrange()
{
	setColor = FVector(1, 0.15f, 0);
}

void ULobbyWidget::SetColorIndigo()
{
	setColor = FVector(0.02f, 0, 0.25);
}

void ULobbyWidget::SetColorBlack()
{
	setColor = FVector(0, 0, 0);
}
