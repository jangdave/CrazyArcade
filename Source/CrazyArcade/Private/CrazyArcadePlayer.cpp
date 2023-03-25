// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyArcadePlayer.h"

#include "Bomb.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "GridTile.h"
#include "EngineUtils.h"

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

