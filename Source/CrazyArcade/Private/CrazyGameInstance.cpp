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

	// �¶��� ���� ������ ���� IOnlinesubsystem Ŭ������ �����´�
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
		// ���� ���� ����
		FOnlineSessionSettings sessionSettings;
		sessionSettings.bAllowInvites = true;
		sessionSettings.bAllowJoinInProgress = true;
		// ������ ���� ����� ����
		sessionSettings.bAllowJoinViaPresence = true;
		// ��������Ʈ ����
		sessionSettings.bIsDedicated = false;
		// �¶��� ����ý����� �̸��� ���̸� ����Ī, �����̸� �������� ��Ī
		sessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
		sessionSettings.NumPublicConnections = playerCount;
		sessionSettings.Set(FName("KEY_RoomName"), roomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		// �ٸ� ����� �ܺ� �˻� ����
		sessionSettings.bShouldAdvertise = true;
		// ���� ����
		sesInterface->CreateSession(0, sessionID, sessionSettings);

		UE_LOG(LogTemp, Warning, TEXT("- Create Session try!"))
	}
}

void UCrazyGameInstance::FindMySession()
{
	// ã������ ���� ������ ����
	sesSearch = MakeShareable(new FOnlineSessionSearch());

	sesSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	sesSearch->MaxSearchResults = 30;

	// presence�� ������ ������ ���͸�
	sesSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	// �տ��� ���� ������ �̿��ؼ� ������ ã�´�
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
		// �˻� ����� �迭�� ��� �α� Ȯ��
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