// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// 로비 페이지
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* horizonBox_PlayerList1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* horizonBox_PlayerList2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_BackLobby;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_ReadyGame;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_StartGame;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Blue;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Green;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Yellow;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Red;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Pink;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Orange;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Indigo;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Black;

	UFUNCTION()
	void StartLevel();

	UFUNCTION()
	void BackLobby();

	// 색상 선택 함수
	UFUNCTION()
	void SetColorBlue();

	UFUNCTION()
	void SetColorGreen();

	UFUNCTION()
	void SetColorYellow();

	UFUNCTION()
	void SetColorRed();

	UFUNCTION()
	void SetColorPink();

	UFUNCTION()
	void SetColorOrange();

	UFUNCTION()
	void SetColorIndigo();

	UFUNCTION()
	void SetColorBlack();

	UPROPERTY()
	FVector setColor;

	FORCEINLINE FVector SetColor() { return setColor; };

	class AStartWidgetController* controller;
};
