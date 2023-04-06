// Fill out your copyright notice in the Description page of Project Settings.


#include "WinWidget.h"

#include "CrazyArcadePlayer.h"
#include "CrazyArcadePlayerController.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void UWinWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Results = { text_WinLose1, text_WinLose2, text_WinLose3, text_WinLose4, text_WinLose5, text_WinLose6, text_WinLose7, text_WinLose8 };
	Names = { text_Name1, text_Name2, text_Name3, text_Name4, text_Name5, text_Name6, text_Name7, text_Name8 };
}