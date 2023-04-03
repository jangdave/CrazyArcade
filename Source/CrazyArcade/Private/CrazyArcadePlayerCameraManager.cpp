// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyArcadePlayerCameraManager.h"

#include "CrazyArcadePlayer.h"
#include "MainCamera.h"

void ACrazyArcadePlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	auto player = Cast<ACrazyArcadePlayer>(GetOwner());

	if (player)
	{
		SetViewTarget(player->MainCamera);
	}
}
