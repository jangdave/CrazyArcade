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
		// �˻� ����� �迭�� ��� �α� Ȯ��
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
