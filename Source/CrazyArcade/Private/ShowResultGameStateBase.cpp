// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowResultGameStateBase.h"

#include "CrazyArcadePlayer.h"
#include "CrazyArcadePlayerController.h"
#include "Components/TextBlock.h"

void AShowResultGameStateBase::BeginPlay()
{
	Super::BeginPlay();


}

void AShowResultGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

void AShowResultGameStateBase::SetResult()
{
	auto players = GetWorld()->GetGameState()->PlayerArray;

	if (!players.IsEmpty())
	{
		for (int i = 0; i < players.Num(); i++)
		{
			Names[i]->SetText(FText::FromString(players[i]->GetPlayerName()));
		}

		for (int i = 0; i < players.Num(); i++)
		{
			auto playerController = Cast<ACrazyArcadePlayerController>(players[i]->GetOwningController());
			if (playerController != nullptr)
			{
				auto player = Cast<ACrazyArcadePlayer>(playerController->GetPawn());
				if (player != nullptr)
				{

					if (player->bIsDead)
					{
						Results[i]->SetText(FText::FromString(FString("Lose")));
						text_PlayerWinLose->SetText(FText::FromString(FString("Lose")));
					}
					else
					{
						Results[i]->SetText(FText::FromString(FString("Win")));
						text_PlayerWinLose->SetText(FText::FromString(FString("Win")));
					}
				}
			}
		}
	}
}
