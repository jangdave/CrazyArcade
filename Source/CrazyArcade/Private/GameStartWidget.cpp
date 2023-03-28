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

	// ���� �ν��Ͻ� ĳ��Ʈ
	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());

	if(gameInstance)
	{

	}

	// �Է� �ʵ� �� ĭ���� �ʱ�ȭ
	editText_ID->SetText(FText::FromString(""));
	editText_RoomName->SetText(FText::FromString(""));
	sl_PlayerCount->SetValue(2.0f);
	text_PlayerCount->SetText(FText::FromString("2"));

	// ������ �Լ� ���ε�
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
