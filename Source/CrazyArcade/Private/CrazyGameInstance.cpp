// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyGameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

UCrazyGameInstance::UCrazyGameInstance()
{
	sessionID = "Test Session";
}

void UCrazyGameInstance::Init()
{
	Super::Init();

	// 온라인 세션 정보를 담은 IOnlinesubsystem 클래스를 가져온다
	IOnlineSubsystem* subsys = IOnlineSubsystem::Get();

	if(subsys)
	{
		sesInterface = subsys->GetSessionInterface();

		if(sesInterface)
		{
			sesInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCrazyGameInstance::CreateSessionComplete);
			sesInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCrazyGameInstance::FindSessionComplete);
			sesInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UCrazyGameInstance::JoinSessionComplete);
		}
	}
}

void UCrazyGameInstance::CreateMySession(FString roomName, int32 playerCount)
{
	if(sesInterface)
	{
		// 세션 정보 생성
		FOnlineSessionSettings sessionSettings;
		sessionSettings.bAllowInvites = true;
		sessionSettings.bAllowJoinInProgress = true;
		// 레벨을 가진 사람만 들어옴
		sessionSettings.bAllowJoinViaPresence = true;
		// 데디케이트 서버
		sessionSettings.bIsDedicated = false;
		// 온라인 서브시스템의 이름이 널이면 랜매칭, 스팀이면 스팀서버 매칭
		sessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
		sessionSettings.NumPublicConnections = playerCount;
		sessionSettings.Set(FName("KEY_RoomName"), roomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		// 다른 사람이 외부 검색 가능
		sessionSettings.bShouldAdvertise = true;
		// 세션 생성
		sesInterface->CreateSession(0, sessionID, sessionSettings);

		UE_LOG(LogTemp, Warning, TEXT("- Create Session try!"))
	}
}

void UCrazyGameInstance::CreateSessionComplete(FName sessionName, bool bSuccess)
{
	FString result = bSuccess ? TEXT("create session success") : TEXT("create session failed");

	UE_LOG(LogTemp, Warning, TEXT("%s : %s"), *result, *sessionName.ToString());

	if(bSuccess)
	{
		GetWorld()->ServerTravel("/Game/Maps/MainLevel?Listen");
	}
}

void UCrazyGameInstance::FindSessionComplete(bool bSuccess)
{
	if(bSuccess)
	{
		// 검색 결과를 배열에 담고 로그 확인
		TArray<FOnlineSessionSearchResult> searchResults = sesSearch->SearchResults;
		UE_LOG(LogTemp, Warning, TEXT("find session count : %d"), searchResults.Num());

		for(int32 i = 0; i<searchResults.Num(); i++)
		{
			//FSessionInfo searchedSessionInfo;
		}
	}
}

void UCrazyGameInstance::JoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type joinResult)
{

}
