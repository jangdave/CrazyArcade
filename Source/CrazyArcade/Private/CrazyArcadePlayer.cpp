// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyArcadePlayer.h"
#include "Bomb.h"
#include "CrazyArcadePlayerController.h"
#include "CrazyGameInstance.h"
#include "CrazyGameStateBase.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "GridTile.h"
#include "EngineUtils.h"
#include "MainCamera.h"
#include "StunBomb.h"
#include "LobbyWidget.h"
#include "ShowResultGameStateBase.h"
#include "Components/CapsuleComponent.h"
#include "StartWidgetController.h"
#include "WinWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACrazyArcadePlayer::ACrazyArcadePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempSkeletal(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if(TempSkeletal.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempSkeletal.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));

}

// Called when the game starts or when spawned
void ACrazyArcadePlayer::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	if(PlayerController)
	{
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

		if (LocalPlayer)
		{
			UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

			if (InputSubsystem)
			{
				InputSubsystem->AddMappingContext(IMC_Player, 0);
			}
		}
	}

	// 캐릭터 색상 변경
	UMaterialInterface* base_mat1 = GetMesh()->GetMaterial(0);
	UMaterialInterface* base_mat2 = GetMesh()->GetMaterial(1);

	if(base_mat1 != nullptr && base_mat2 != nullptr)
	{
		mat1 = UMaterialInstanceDynamic::Create(base_mat1, this);
		GetMesh()->SetMaterial(0, mat1);

		mat2 = UMaterialInstanceDynamic::Create(base_mat2, this);
		GetMesh()->SetMaterial(1, mat2);
	}
	
	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());
	gs = Cast<ACrazyGameStateBase>(GetWorld()->GetGameState());
	startCont = Cast<AStartWidgetController>(GetWorld()->GetFirstPlayerController());
	ShowResultState = Cast<AShowResultGameStateBase>(GetWorld()->GetGameState());
	// WinWidget = CreateWidget<UWinWidget>(GetWorld(), WinWidgetFactory);

	// 플레이어 스테이트에 이름 저장
	if(GetController() != nullptr && GetController()->IsLocalController())
	{
		ServerSetName(gameInstance->sessionID.ToString());
	}

	for(TActorIterator<AGridTile> itr(GetWorld()); itr; ++itr)
	{
		GridTiles.Add(*itr);
	}

	/*if(HasAuthority())
	{
		PlayersNum = GetWorld()->GetGameState()->PlayerArray.Num();
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay PlayersNum: %d"), PlayersNum);
	}*/
}

// Called every frame
void ACrazyArcadePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 캐릭터 색상 & 위젯 버튼 색상
	if (GetController() != nullptr && GetController()->IsLocalController())
	{
		ServerSetColor(gameInstance->setMatColor);
		
		if(startCont != nullptr)
		{
			ServerColor(gameInstance->setMatColor, bCheckReady);
		}
	}

	if(HasAuthority())
	{
		if(startCont != nullptr && startCont->lobbyWid != nullptr)
		{
			if (GetWorld()->GetGameState()->PlayerArray.Num() == gs->checkCount)
			{
				startCont->lobbyWid->btn_StartGame->SetIsEnabled(true);
			}
		}
	}
}

// Called to bind functionality to input
void ACrazyArcadePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	InputComp->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ACrazyArcadePlayer::Move);
	InputComp->BindAction(IA_Bomb, ETriggerEvent::Started, this, &ACrazyArcadePlayer::SpawnBomb);
}

void ACrazyArcadePlayer::ServerWinWidget_Implementation()
{
	// CreateWinWidget();
	FTimerHandle winTimer;
	GetWorldTimerManager().SetTimer(winTimer, FTimerDelegate::CreateLambda([this]()->void
		{
			ShowResultState->WinWidget->AddToViewport();
		}), 3.f, false);
	MulticastWinWidget();
}

void ACrazyArcadePlayer::MulticastWinWidget_Implementation()
{
	//CreateWinWidget();

	FTimerHandle winTimer;
	GetWorldTimerManager().SetTimer(winTimer, FTimerDelegate::CreateLambda([this]()->void
		{
			ShowResultState->WinWidget->AddToViewport();
		}), 3.f, false);
}

void ACrazyArcadePlayer::CreateWinWidget()
{
	FTimerHandle winTimer;
	GetWorldTimerManager().SetTimer(winTimer, FTimerDelegate::CreateLambda([this]()->void
		{
			WinWidget->AddToViewport(100);
			UE_LOG(LogTemp, Warning, TEXT("PlayersNum AddToViewport: %d"), PlayersNum);
		}), 3.f, false);
}

void ACrazyArcadePlayer::Move(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();
	FRotator MovementRotation = Controller->GetControlRotation() + FRotator(0.f, -90.f, 0.f);
	FVector directionForward = MovementRotation.RotateVector(FVector::ForwardVector);
	FVector directionRight = MovementRotation.RotateVector(FVector::RightVector);

	if (Axis.X != 0)
	{
		AddMovementInput(directionForward, Axis.X);
	}
	else if (Axis.Y != 0)
	{
		AddMovementInput(directionRight, Axis.Y);
	}
}

void ACrazyArcadePlayer::SpawnBomb()
{
	if(HasAuthority())
	{
		float distnaceToNearest = 0.f;
		AGridTile* NearestTile = FindNearstTile(GetActorLocation(), GridTiles, distnaceToNearest);
		GetWorld()->SpawnActor<ABomb>(BombFactory, NearestTile->GetActorLocation(), NearestTile->GetActorRotation());
	}
	else
	{
		ClientSpawnBomb();
	}
}

void ACrazyArcadePlayer::ClientSpawnBomb_Implementation()
{
	float distnaceToNearest = 0.f;
	AGridTile* NearestTile = FindNearstTile(GetActorLocation(), GridTiles, distnaceToNearest);
	GetWorld()->SpawnActor<ABomb>(BombFactory, NearestTile->GetActorLocation(), NearestTile->GetActorRotation());

	ServerSpawnBomb();
}

void ACrazyArcadePlayer::ServerSpawnBomb_Implementation()
{
	float distnaceToNearest = 0.f;
	AGridTile* NearestTile = FindNearstTile(GetActorLocation(), GridTiles, distnaceToNearest);
	GetWorld()->SpawnActor<ABomb>(BombFactory, NearestTile->GetActorLocation(), NearestTile->GetActorRotation());
}

void ACrazyArcadePlayer::ClientStun_Implementation()
{
	SpawnStunBomb();
	ServerStun();
}

void ACrazyArcadePlayer::ServerStun_Implementation()
{
	SpawnStunBomb();
	MulticastStun();
}

void ACrazyArcadePlayer::MulticastStun_Implementation()
{
	SpawnStunBomb();
}

void ACrazyArcadePlayer::SpawnStunBomb()
{
	float distnaceToNearest = 0.f;
	AGridTile* NearestTile = FindNearstTile(GetActorLocation(), GridTiles, distnaceToNearest);
	StunBomb = GetWorld()->SpawnActor<AStunBomb>(StunBombFactory, NearestTile->GetActorLocation(), NearestTile->GetActorRotation());
	AttachToActor(StunBomb, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	UnPossessed();
	GetCharacterMovement()->StopMovementImmediately();
	FTimerHandle dieHandle;
	GetWorldTimerManager().SetTimer(dieHandle, FTimerDelegate::CreateLambda([&]()->void
	{
		// Destroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetVisibility(false);
		bIsDead = true;
	}), 3.f, false, 3.f);


	if(HasAuthority())
	{
		ShowResultState->PlayersNum--;
	}
	UE_LOG(LogTemp, Warning, TEXT("%d: PlayersNum"), PlayersNum);
	if (ShowResultState->PlayersNum <= 1)
	{
		PlayersNum = ShowResultState->PlayersNum;
		ServerWinWidget();
	}
}

AGridTile* ACrazyArcadePlayer::FindNearstTile(FVector Origin, const TArray<AGridTile*>& TilesToCheck, float& Distance)
{
	AGridTile* NearestTile = nullptr;
	float DistanceFromNearestActor = Distance = TNumericLimits<float>::Max();

	for (AGridTile* TileToCheck : TilesToCheck)
	{
		if (TileToCheck)
		{
			const float DistanceFromActorToCheck = (Origin - TileToCheck->GetActorLocation()).SizeSquared();
			if (DistanceFromActorToCheck < DistanceFromNearestActor)
			{
				NearestTile = TileToCheck;
				DistanceFromNearestActor = DistanceFromActorToCheck;
			}
		}
	}

	if (NearestTile)
	{
		Distance = FMath::Sqrt(DistanceFromNearestActor);
	}

	return NearestTile;
}

void ACrazyArcadePlayer::ServerColor_Implementation(const FVector& color, bool bCheck)
{
	MulticastColor(color, bCheck);
}

void ACrazyArcadePlayer::MulticastColor_Implementation(const FVector& color, bool bCheck)
{
	if (startCont != nullptr && startCont->lobbyWid != nullptr)
	{
		for (int i = 0; i < startCont->lobbyWid->texts.Num(); i++)
		{
			if (startCont->lobbyWid->texts[i]->GetText().ToString() == pName)
			{
				auto button = Cast<UButton>(startCont->lobbyWid->texts[i]->GetParent());

				if(bCheck != true)
				{
					FLinearColor col = FLinearColor{ (float)color.X, (float)color.Y, (float)color.Z, 0.5f};
					button->SetBackgroundColor(col);
				}
				else
				{
					button->SetBackgroundColor((FLinearColor)color);

					if(bOnce != true)
					{
						gs->checkCount++;

						bOnce = true;
					}
				}
			}
			else if(gs->PlayerArray.Num() <= i)
			{
				auto button = Cast<UButton>(startCont->lobbyWid->texts[i]->GetParent());
				
				FLinearColor temp = FLinearColor{1, 1, 1, 1};

				button->SetBackgroundColor(temp);
			}
		}
	}
}

void ACrazyArcadePlayer::ServerSetName_Implementation(const FString& name)
{
	pName = name;

	APlayerState* pp = Cast<APlayerState>(GetPlayerState());

	if (pp != nullptr)
	{
		// 해당 플레이어에 대한 이름 변경
		pp->SetPlayerName(name);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *name);
	}
}

void ACrazyArcadePlayer::ServerSetColor_Implementation(const FVector& color)
{
	MulticastSetColor(color);
}

void ACrazyArcadePlayer::MulticastSetColor_Implementation(const FVector& color)
{
	if(mat1 != nullptr && mat2 != nullptr)
	{
		mat1->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
		mat2->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
	}
}

void ACrazyArcadePlayer::KickPlayer(const FString& text)
{
	if (HasAuthority())
	{
		for (TActorIterator<ACrazyArcadePlayer> pl(GetWorld()); pl; ++pl)
		{
			ACrazyArcadePlayer* p = *pl;

			if (p->pName == text)
			{
				p->EndSession();

				p->bCheckReady = false;
			}
		}
	}
}

void ACrazyArcadePlayer::EndSession()
{
	gameInstance->sesInterface->EndSession(gameInstance->sessionID);
	
	// 레벨을 다시 처음 위치로 이동
	AStartWidgetController* pc = Cast<AStartWidgetController>(GetController());
	pc->ClientTravel(FString("/Game/Maps/LobbyMap'"), ETravelType::TRAVEL_Relative);
}

void ACrazyArcadePlayer::DestroyGame()
{
	if (HasAuthority())
	{
		for (TActorIterator<ACrazyArcadePlayer> pl(GetWorld()); pl; ++pl)
		{
			ACrazyArcadePlayer* p = *pl;

			if (p != this)
			{
				p->ServerDestroyGame();
			}
		}
		FTimerHandle testHandle;
		GetWorldTimerManager().SetTimer(testHandle, this, &ACrazyArcadePlayer::EndGame, 1.0f, false);
	}
	else
	{
		EndGame();
	}
}

void ACrazyArcadePlayer::EndGame()
{
	gameInstance->sesInterface->DestroySession(gameInstance->sessionID);

	// 레벨을 다시 처음 위치로 이동
	ACrazyArcadePlayerController* pc = Cast<ACrazyArcadePlayerController>(GetController());
	pc->ClientTravel(FString("/Game/Maps/LobbyMap'"), ETravelType::TRAVEL_Relative);
}

void ACrazyArcadePlayer::ServerDestroyGame_Implementation()
{
	MulticastDestroyGame();
}

void ACrazyArcadePlayer::MulticastDestroyGame_Implementation()
{
	if (GetController() != nullptr && GetController()->IsLocalController())
	{
		EndGame();
	}
}

void ACrazyArcadePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACrazyArcadePlayer, mat1);
	DOREPLIFETIME(ACrazyArcadePlayer, mat2);
	DOREPLIFETIME(ACrazyArcadePlayer, pName);
	DOREPLIFETIME(ACrazyArcadePlayer, bCheckReady);
	DOREPLIFETIME(ACrazyArcadePlayer, bCheckReadyList);
	DOREPLIFETIME(ACrazyArcadePlayer, PlayersNum);
}
