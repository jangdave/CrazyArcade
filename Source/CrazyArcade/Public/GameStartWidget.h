// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* widgetSwitcher;

	// 로그인 페이지
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* editText_ID;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Login;

	// 룸리스트 페이지
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* sbox_RoomList;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_CreateRoom;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_RefreshRoom;

	// 방생성 페이지
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* editText_RoomName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_BackCreateRoom;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_CreateLobby;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class USlider* sl_PlayerCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* text_PlayerCount;
	
	class UCrazyGameInstance* gameInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class URoomSlotWidget> roomWidget;

	UFUNCTION()
	void ClickStartGame();

	UFUNCTION()
	void CreateGameRoom();

	UFUNCTION()
	void CreateLobby();

	UFUNCTION()
	void MoveSlide(float value);

	UFUNCTION()
	void BackCreateRoom();

	UFUNCTION()
	void AddNewSlot(FSessionInfo sessionInfo);

	UFUNCTION()
	void RefreshEnabled();

	UFUNCTION()
	void RefreshList();

	UFUNCTION()
	void InLobby();
};