// Fill out your copyright notice in the Description page of Project Settings.


#include "CrazyArcadePlayerController.h"

#include "MainCamera.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InGameWidget.h"

void ACrazyArcadePlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*MainCamera = Cast<AMainCamera>(GetWorld()->SpawnActor<ACameraActor>(CameraFactory));
	UE_LOG(LogTemp, Warning, TEXT("Camera"));
	MainCamera->SetActorLocationAndRotation(FVector(170.f, 650.f, 5450.f), FRotator(-90.f, 0.f, 0.f));


	if(IsLocalController())
	{
		SetViewTarget(MainCamera);
	}*/

	InGameWidget = CreateWidget<UInGameWidget>(GetWorld(), InGameWidgetFactory);
	if(InGameWidget && IsLocalController())
	{
		InGameWidget->AddToViewport();
		SetShowMouseCursor(true);
	}
}
