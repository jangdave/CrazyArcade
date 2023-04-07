// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Text_Player0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_Player1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_Player2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_Player3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_Player4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_Player5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_Player6;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_Player7;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UButton* btn_Quit;

	TArray<UTextBlock*> playerNames;

	UFUNCTION()
	void SetName();

	UFUNCTION()
	void QuitGame();

	class ACrazyArcadePlayer* player;
};
