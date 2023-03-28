// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CrazyGameInstance.generated.h"

/**
 * 
 */

USTRUCT()
struct FSessionInfo
{
	GENERATED_BODY()

	FString roomName;
	int32 currentPlayers;
	int32 maxPlayers;
	int32 ping;
	int32 idx;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSearchResult, FSessionInfo, sessionInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSearchFinished);

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

	FOnSearchResult ResultDele;

	FOnSearchFinished FinishedDele;

	UPROPERTY()
	bool bIsSuccess;
	
	void CreateMySession(FString roomName, int32 playerCount);

	void FindMySession();

	void JoinMySession(int32 sessionIdx);

	UFUNCTION()
	void CreateSessionComplete(FName sessionName, bool bSuccess);

	UFUNCTION()
	void FindSessionComplete(bool bSuccess);

	void JoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type joinResult);
};