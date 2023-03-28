// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomSlotWidget.h"
#include "CrazyGameInstance.h"
#include "Components/Button.h"

void URoomSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());

	btn_RoomName->OnClicked.AddDynamic(this, &URoomSlotWidget::JoinRoom);
}

void URoomSlotWidget::JoinRoom()
{
	if(gameInstance)
	{
		gameInstance->JoinMySession(index);
	}
}
