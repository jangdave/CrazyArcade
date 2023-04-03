// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidgetController.h"
#include "CrazyArcadePlayer.h"
#include "CrazyGameInstance.h"
#include "LobbyWidget.h"
#include "LobbyPlayerWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AStartWidgetController::AStartWidgetController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStartWidgetController::BeginPlay()
{
	Super::BeginPlay();

	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());

	owner = Cast<ACrazyArcadePlayer>(GetCharacter());

	SetOwner(owner);

	if(lobbyWidget != nullptr && IsLocalController())
	{
		lobbyWid = CreateWidget<ULobbyWidget>(this, lobbyWidget);

		lobbyWid->AddToViewport();

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		
		ServerPlayWidget();
	}
}

void AStartWidgetController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AStartWidgetController::ServerPlayWidget_Implementation()
{
	MulticastPlayWidget();
}

void AStartWidgetController::MulticastPlayWidget_Implementation()
{
	auto playerWid = CreateWidget<ULobbyPlayerWidget>(this, playerWidget);

	if (playerWid != nullptr)
	{
		playerWid->text_PlayerName->SetText(FText::FromName(gameInstance->GetName()));

		lobbyWid->horizonBox_PlayerList1->AddChild(playerWid);
	}
}

void AStartWidgetController::SetColor()
{
	//if (lobbyWid != nullptr)
	//{
	//	color = lobbyWid->SetColor();

	//	auto owner = Cast<ACrazyArcadePlayer>(GetOwner());
		
		//UE_LOG(LogTemp, Warning, TEXT("%f / %f / %f"), color.X, color.Y, color.Z)

	//	owner->mat1->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
	//	owner->mat2->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
	//}
	//else
	
	SetServerColor();
	
	
}

void AStartWidgetController::SetServerColor_Implementation()
{
	if (lobbyWid != nullptr)
	{
		color = lobbyWid->SetColor();

		//UE_LOG(LogTemp, Warning, TEXT("%f / %f / %f"), color.X, color.Y, color.Z)

		owner->mat1->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
		owner->mat2->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
	}
	//SetMulticastColor();
}

void AStartWidgetController::SetMulticastColor_Implementation()
{
	if(lobbyWid != nullptr)
	{
		color = lobbyWid->SetColor();

		//UE_LOG(LogTemp, Warning, TEXT("%f / %f / %f"), color.X, color.Y, color.Z)
		
		owner->mat1->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
		owner->mat2->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
	}
}

void AStartWidgetController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AStartWidgetController, color);
}