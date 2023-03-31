// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"
#include "GameStartWidget.h"
#include "Kismet/GameplayStatics.h"

void ALoginGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	gameStart_UI = CreateWidget<UGameStartWidget>(GetWorld(), gameStartWidget);

	gameStart_UI->AddToViewport();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}
