// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"
#include "CrazyGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "RoomSlotWidget.h"
#include "Components/ScrollBox.h"

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 게임 인스턴스 캐스트
	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());

	if(gameInstance)
	{
		gameInstance->ResultDele.AddDynamic(this, &UGameStartWidget::AddNewSlot);
		gameInstance->FinishedDele.AddDynamic(this, &UGameStartWidget::RefreshEnabled);
	}

	// 입력 필드 빈 칸으로 초기화
	editText_ID->SetText(FText::FromString(""));
	editText_RoomName->SetText(FText::FromString(""));
	sl_PlayerCount->SetValue(2.0f);
	text_PlayerCount->SetText(FText::FromString("2"));

	// 위젯에 함수 바인드
	btn_Login->OnClicked.AddDynamic(this, &UGameStartWidget::ClickStartGame);
	btn_CreateRoom->OnClicked.AddDynamic(this, &UGameStartWidget::CreateGameRoom);
	btn_CreateLobby->OnClicked.AddDynamic(this, &UGameStartWidget::CreateLobby);
	sl_PlayerCount->OnValueChanged.AddDynamic(this, &UGameStartWidget::MoveSlide);
	btn_BackCreateRoom->OnClicked.AddDynamic(this, &UGameStartWidget::BackCreateRoom);
	btn_BackLobby->OnClicked.AddDynamic(this, &UGameStartWidget::BackLobby);
	btn_RefreshRoom->OnClicked.AddDynamic(this, &UGameStartWidget::RefreshList);
	btn_StartGame->OnClicked.AddDynamic(this, &UGameStartWidget::StartLevel);
}

void UGameStartWidget::ClickStartGame()
{
	if(editText_ID->GetText().IsEmpty() != true)
	{
		widgetSwitcher->SetActiveWidgetIndex(1);
		
		gameInstance->sessionID = FName(*editText_ID->GetText().ToString());
	}
}

void UGameStartWidget::CreateGameRoom()
{
	widgetSwitcher->SetActiveWidgetIndex(2);
}

void UGameStartWidget::CreateLobby()
{
	int32 playerCnt = FMath::RoundFromZero(sl_PlayerCount->GetValue());

	gameInstance->CreateMySession(editText_RoomName->GetText().ToString(), playerCnt);

	if(gameInstance->bIsSuccess != false)
	{
		widgetSwitcher->SetActiveWidgetIndex(3);
	}
}

void UGameStartWidget::MoveSlide(float value)
{
	int32 setCnt = FMath::RoundHalfToZero(value);
	text_PlayerCount->SetText(FText::AsNumber(setCnt));
}

void UGameStartWidget::BackCreateRoom()
{
	widgetSwitcher->SetActiveWidgetIndex(1);
}

void UGameStartWidget::BackLobby()
{
	//widgetSwitcher->SetActiveWidgetIndex(1);
}

void UGameStartWidget::AddNewSlot(FSessionInfo sessionInfo)
{
	auto roomWid = CreateWidget<URoomSlotWidget>(this, roomWidget);

	if(roomWid != nullptr)
	{
		roomWid->text_RoomName->SetText(FText::FromString(sessionInfo.roomName));
		roomWid->text_PlayerInfo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), sessionInfo.currentPlayers, sessionInfo.maxPlayers)));
		roomWid->text_Ping->SetText(FText::FromString(FString::Printf(TEXT("%d ms"), sessionInfo.ping)));
		roomWid->index = sessionInfo.idx;

		sbox_RoomList->AddChild(roomWid);
	}
}

void UGameStartWidget::RefreshEnabled()
{
	btn_RefreshRoom->SetIsEnabled(true);
}

void UGameStartWidget::StartLevel()
{
	GetWorld()->ServerTravel("/Game/Maps/MainLevel?Listen");
}

void UGameStartWidget::RefreshList()
{
	sbox_RoomList->ClearChildren();

	gameInstance->FindMySession();

	btn_RefreshRoom->SetIsEnabled(false);
}
