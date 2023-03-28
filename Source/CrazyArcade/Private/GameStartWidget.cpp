// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"
#include "CrazyGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 게임 인스턴스 캐스트
	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());

	if(gameInstance)
	{

	}

	// 입력 필드 빈 칸으로 초기화
	editText_ID->SetText(FText::FromString(""));
	editText_RoomName->SetText(FText::FromString(""));
	sl_PlayerCount->SetValue(2.0f);
	text_PlayerCount->SetText(FText::FromString("2"));

	// 위젯에 함수 바인드
	btn_Login->OnClicked.AddDynamic(this, &UGameStartWidget::ClickStartGame);
}

void UGameStartWidget::ClickStartGame()
{
	if(editText_ID->GetText().IsEmpty() != true)
	{
		widgetSwitcher->SetActiveWidgetIndex(1);

		gameInstance->sessionID = FName(*editText_ID->GetText().ToString());
	}
}
