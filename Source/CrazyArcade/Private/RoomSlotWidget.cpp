// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomSlotWidget.h"
#include "CrazyGameInstance.h"
#include "Components/Button.h"
#include "GameStartWidget.h"
#include "GameFramework/GameStateBase.h"

void URoomSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());

	startWid = CreateWidget<UGameStartWidget>(this, startWidget);

	btn_RoomName->OnClicked.AddDynamic(this, &URoomSlotWidget::JoinRoom);
}

void URoomSlotWidget::JoinRoom()
{
	if(gameInstance != nullptr)
	{
		gameInstance->JoinMySession(index);

		//GetWorld()->GetGameInstance()->
	}
}
