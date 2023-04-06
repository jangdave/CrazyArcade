// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "CrazyArcadePlayer.h"
#include "CrazyLobbyPlayerState.h"
#include "StartWidgetController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_BackLobby->OnClicked.AddDynamic(this, &ULobbyWidget::BackLobby);
	btn_StartGame->OnClicked.AddDynamic(this, &ULobbyWidget::StartLevel);

	// 색상 선택
	btn_Blue->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorBlue);
	btn_Green->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorGreen);
	btn_Yellow->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorYellow);
	btn_Red->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorRed);
	btn_Pink->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorPink);
	btn_Orange->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorOrange);
	btn_Indigo->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorIndigo);
	btn_Black->OnClicked.AddDynamic(this, &ULobbyWidget::SetColorBlack);

	controller = Cast<AStartWidgetController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	player = Cast<ACrazyArcadePlayer>(GetOwningPlayerPawn());

	texts = { text_Player0, text_Player1, text_Player2, text_Player3, text_Player4, text_Player5, text_Player6, text_Player7 };

	buttons = { btn_Player0, btn_Player1, btn_Player2, btn_Player3, btn_Player4, btn_Player5, btn_Player6, btn_Player7 };
}

void ULobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetName();
}

void ULobbyWidget::StartLevel()
{
	GetWorld()->ServerTravel("/Game/Maps/MainLevel?Listen");
}

void ULobbyWidget::BackLobby()
{

}

void ULobbyWidget::SetColorBlue()
{
	setColor = FVector(0, 0, 1);

	controller->SetColor();
}

void ULobbyWidget::SetColorGreen()
{
	setColor = FVector(0, 1, 0);

	controller->SetColor();
}

void ULobbyWidget::SetColorYellow()
{
	setColor = FVector(1, 1, 0);

	controller->SetColor();
}

void ULobbyWidget::SetColorRed()
{
	setColor = FVector(1, 0, 0);

	controller->SetColor();
}

void ULobbyWidget::SetColorPink()
{
	setColor = FVector(1, 0, 1);

	controller->SetColor();
}

void ULobbyWidget::SetColorOrange()
{
	setColor = FVector(1, 0.15f, 0);

	controller->SetColor();
}

void ULobbyWidget::SetColorIndigo()
{
	setColor = FVector(0.02f, 0, 0.25);

	controller->SetColor();
}

void ULobbyWidget::SetColorBlack()
{
	setColor = FVector(0, 0, 0);

	controller->SetColor();
}

void ULobbyWidget::SetName()
{
	auto array = GetWorld()->GetGameState()->PlayerArray;

	for (int i = 0; i < array.Num(); i++)
	{
		texts[i]->SetText(FText::FromString(array[i]->GetPlayerName()));

		//auto state = Cast<ACrazyLobbyPlayerState>(array[i]);

		//buttons[i]->SetBackgroundColor(state->SetButtonColor);
	}
}

// 배열을 접속 시간 순서대로 배열해서 해보기

// 서버 함수로 실행

//auto playerState = Cast<ACrazyLobbyPlayerState>(player->GetPlayerState());
