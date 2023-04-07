// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowResultGameStateBase.h"

#include "CrazyArcadePlayer.h"
#include "CrazyArcadePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WinWidget.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

AShowResultGameStateBase::AShowResultGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShowResultGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	WinWidget = CreateWidget<UWinWidget>(GetWorld(), WinWidgetFactory);
	Player = Cast<ACrazyArcadePlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AShowResultGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PlayersNum = UGameplayStatics::GetGameState(GetWorld())->PlayerArray.Num();

	if(GetWorld()->GetGameState() == nullptr)
	{
		return;
	}

	if (WinWidget != nullptr && Player != nullptr && Player->PlayersNum <= 1)
	{
		SetResult();
	}
}

void AShowResultGameStateBase::SetResult()
{
	auto players = UGameplayStatics::GetGameState(GetWorld())->PlayerArray;
	
	
	if(WinWidget == nullptr)
	{
		return;
	}

	if (!players.IsEmpty() && HasAuthority())
	{
		for (int i = 0; i < players.Num(); i++)
		{
			WinWidget->Names[i]->SetText(FText::FromString(FString("aa")));//players[i]->GetPlayerName()));
		}
		
		for (int i = 0; i < players.Num(); i++)
		{
			auto playerController = Cast<ACrazyArcadePlayerController>(players[i]->GetOwningController());
			if (playerController != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Result Has Controller"));
				auto player = Cast<ACrazyArcadePlayer>(playerController->GetPawn());
				// auto player = Cast<ACrazyArcadePlayer>(GetOwner());
				if (player != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("Result Has Player"));

					if (player->bIsDead)
					{
						WinWidget->Results[i]->SetText(FText::FromString(FString("Lose")));
						WinWidget->text_PlayerWinLose->SetText(FText::FromString(FString("Lose")));
					}
					else
					{
						WinWidget->Results[i]->SetText(FText::FromString(FString("Win")));
						WinWidget->text_PlayerWinLose->SetText(FText::FromString(FString("Win")));
					}
				}
			}
		}
	}
}
