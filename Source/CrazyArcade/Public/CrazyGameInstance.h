// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CrazyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API UCrazyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCrazyGameInstance();

	virtual void Init() override;

	IOnlineSessionPtr sesInterface;

	FName sessionID;

	TSharedPtr<FOnlineSessionSearch> sesSearch;

	//FOnSearchResult ResultDele;

	//FOnsearchFinished FinishedDele;

	void CreateMySession(FString roomName, int32 playerCount);

	void CreateSessionComplete(FName sessionName, bool bSuccess);

	void FindSessionComplete(bool bSuccess);

	void JoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type joinResult);
};