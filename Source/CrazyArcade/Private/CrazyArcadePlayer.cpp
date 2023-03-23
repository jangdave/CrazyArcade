// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyArcadePlayer.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ACrazyArcadePlayer::ACrazyArcadePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArm);
	// CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	// CameraComponent->SetOrthoWidth(2000.f);
	CameraComponent->SetRelativeLocation(FVector(-600.f, 0.f, 0.f));

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
	InputComp->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ACrazyArcadePlayer::Turn);
}

void ACrazyArcadePlayer::Move(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), Axis.X);
	AddMovementInput(GetActorRightVector(), Axis.Y);

}

void ACrazyArcadePlayer::Turn(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();
	AddControllerPitchInput(Axis.Y);
	AddControllerYawInput(Axis.X);
}

