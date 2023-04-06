// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyArcadePlayer.h"
#include "Bomb.h"
#include "CrazyArcadePlayerController.h"
#include "CrazyGameInstance.h"
#include "CrazyLobbyPlayerState.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "GridTile.h"
#include "EngineUtils.h"
#include "MainCamera.h"
#include "StunBomb.h"
#include "LobbyWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	MainCamera = Cast<AMainCamera>(GetWorld()->SpawnActor<ACameraActor>(CameraFactory));
	MainCamera->SetActorLocationAndRotation(FVector(170.f, 650.f, 5450.f), FRotator(-90.f, 0.f, 0.f));
	if(MainCamera)
	{
		if(PlayerController->IsLocalController())
		{
			PlayerController->SetViewTarget(MainCamera);
			UE_LOG(LogTemp, Warning, TEXT("Camera SetView"));
			//ServerSpawnCamera();
		}
	}

	// ĳ���� ���� ����
	UMaterialInterface* base_mat1 = GetMesh()->GetMaterial(0);
	UMaterialInterface* base_mat2 = GetMesh()->GetMaterial(1);

	if(base_mat1 != nullptr && base_mat2 != nullptr)
	{
		mat1 = UMaterialInstanceDynamic::Create(base_mat1, this);
		GetMesh()->SetMaterial(0, mat1);

		mat2 = UMaterialInstanceDynamic::Create(base_mat2, this);
		GetMesh()->SetMaterial(1, mat2);
	}

	lobby_Wid = CreateWidget<ULobbyWidget>(GetWorld(), lobby_UI);
	gameInstance = Cast<UCrazyGameInstance>(GetGameInstance());
	pstate = Cast<ACrazyLobbyPlayerState>(GetPlayerState());

	// �÷��̾� ������Ʈ�� �̸� ����
	if(GetController() != nullptr && GetController()->IsLocalController())
	{
		ServerSetName(gameInstance->sessionID.ToString());
	}

	for(TActorIterator<AGridTile> itr(GetWorld()); itr; ++itr)
	{
		GridTiles.Add(*itr);
	}
}

// Called every frame
void ACrazyArcadePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetController() != nullptr && GetController()->IsLocalController())
	{
		ServerSetColor(gameInstance->setMatColor);

		if(pstate != nullptr)
		{
			ServerColor(gameInstance->setMatColor);
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
	float distnaceToNearest = 0.f;
	AGridTile* NearestTile = FindNearstTile(GetActorLocation(), GridTiles, distnaceToNearest);
	GetWorld()->SpawnActor<ABomb>(BombFactory, NearestTile->GetActorLocation(), NearestTile->GetActorRotation());
}

void ACrazyArcadePlayer::Stun()
{

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
		Destroy();
	}), 3.f, false, 3.f);
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

void ACrazyArcadePlayer::ServerColor_Implementation(const FVector& color)
{
}

void ACrazyArcadePlayer::MulticastColor_Implementation(const FVector& color)
{
}

//void ACrazyArcadePlayer::ServerColor_Implementation()
//{
//	pstate->SetButtonColor = (FLinearColor)gameInstance->setMatColor;

//	UE_LOG(LogTemp, Warning, TEXT("%f / %f / %f"), pstate->SetButtonColor.R, pstate->SetButtonColor.G, pstate->SetButtonColor.B)
//}

void ACrazyArcadePlayer::ServerSetName_Implementation(const FString& name)
{
	APlayerState* pp = Cast<APlayerState>(GetPlayerState());

	if (pp != nullptr)
	{
		// �ش� �÷��̾ ���� �̸� ����
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
	mat1->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
	mat2->SetVectorParameterValue(FName("Tint"), (FLinearColor)color);
}

void ACrazyArcadePlayer::MulticastSpawnCamera_Implementation()
{
	auto playerController = Cast<ACrazyArcadePlayerController>(GetWorld()->GetFirstPlayerController());

	if (MainCamera)
	{
		if(playerController)
		{
			playerController->SetViewTarget(MainCamera);
			UE_LOG(LogTemp, Warning, TEXT("Camera SetView Multicast"));
		}
	}
}

void ACrazyArcadePlayer::ServerSpawnCamera_Implementation()
{
	// MulticastSpawnCamera();
}

void ACrazyArcadePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACrazyArcadePlayer, mat1);
	DOREPLIFETIME(ACrazyArcadePlayer, mat2);
}