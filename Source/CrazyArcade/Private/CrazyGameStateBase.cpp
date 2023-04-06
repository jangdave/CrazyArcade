// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyGameStateBase.h"
#include "Net/UnrealNetwork.h"

void ACrazyGameStateBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACrazyGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACrazyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACrazyGameStateBase, checkCount);
}