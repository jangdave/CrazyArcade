// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyGameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Net/UnrealNetwork.h"

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

void UCrazyGameInstance::FindMySession()
{
	// 찾으려는 세션 쿼리를 생성
	sesSearch = MakeShareable(new FOnlineSessionSearch());

	sesSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	sesSearch->MaxSearchResults = 30;

	// presence로 생성된 세션을 필터링
	sesSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	// 앞에서 만든 쿼리를 이용해서 세션을 찾는다
	sesInterface->FindSessions(0, sesSearch.ToSharedRef());
}

void UCrazyGameInstance::JoinMySession(int32 sessionIdx)
{
	FOnlineSessionSearchResult selectedSession = sesSearch->SearchResults[sessionIdx];

	sesInterface->JoinSession(0, sessionID, selectedSession);
}

void UCrazyGameInstance::CreateSessionComplete(FName sessionName, bool bSuccess)
{
	FString result = bSuccess ? TEXT("create session success") : TEXT("create session failed");

	UE_LOG(LogTemp, Warning, TEXT("%s : %s"), *result, *sessionName.ToString());

	if(bSuccess)
	{
		bIsSuccess = true;
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
			FSessionInfo searchedSessionInfo;

			FString roomName;
			searchResults[i].Session.SessionSettings.Get(FName("KEY_RoomName"), roomName);
			searchedSessionInfo.roomName = roomName;

			int32 maxPlayers = searchResults[i].Session.SessionSettings.NumPublicConnections;
			searchedSessionInfo.maxPlayers = maxPlayers;

			int32 currentPlayers = maxPlayers - searchResults[i].Session.NumOpenPublicConnections;
			searchedSessionInfo.currentPlayers = currentPlayers;

			int32 ping = searchResults[i].PingInMs;
			searchedSessionInfo.ping = ping;

			searchedSessionInfo.idx = i;

			ResultDele.Broadcast(searchedSessionInfo);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Sessions Failed..."));
	}

	FinishedDele.Broadcast();
}

void UCrazyGameInstance::JoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type joinResult)
{
	if(joinResult == EOnJoinSessionCompleteResult::Success)
	{
		FString joinAddress;

		sesInterface->GetResolvedConnectString(sessionName, joinAddress);

		UE_LOG(LogTemp, Warning, TEXT("join address : %s"), *joinAddress)

		if (APlayerController* pc = GetWorld()->GetFirstPlayerController())
		{
			pc->ClientTravel(joinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UCrazyGameInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCrazyGameInstance, sessionID);
}