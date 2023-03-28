// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"
#include "GameStartWidget.h"

ALoginGameModeBase::ALoginGameModeBase()
{

}

void ALoginGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	gameStart_UI = CreateWidget<UGameStartWidget>(GetWorld(), gameStartWidget);

	gameStart_UI->AddToViewport();
}
