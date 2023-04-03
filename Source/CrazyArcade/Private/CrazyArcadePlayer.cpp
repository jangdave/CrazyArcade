// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyArcadePlayer.h"
#include "Bomb.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "GridTile.h"
#include "EngineUtils.h"
#include "StunBomb.h"
#include "LobbyWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	for(TActorIterator<AGridTile> itr(GetWorld()); itr; ++itr)
	{
		GridTiles.Add(*itr);
	}
}

// Called every frame
void ACrazyArcadePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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