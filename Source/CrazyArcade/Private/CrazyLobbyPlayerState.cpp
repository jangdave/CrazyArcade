// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyLobbyPlayerState.h"
#include "Net/UnrealNetwork.h"

void ACrazyLobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	SetButtonColor = FLinearColor{1, 1, 1, 1};
}

void ACrazyLobbyPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ACrazyLobbyPlayerState::ButtonColor(FVector color)
{
	FLinearColor tempColor = (FLinearColor)color;
	SetButtonColor = tempColor;
}

void ACrazyLobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACrazyLobbyPlayerState, SetButtonColor);
}
