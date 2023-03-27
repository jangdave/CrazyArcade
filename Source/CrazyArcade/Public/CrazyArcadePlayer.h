// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CrazyArcadePlayer.generated.h"

UCLASS()
class CRAZYARCADE_API ACrazyArcadePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACrazyArcadePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category="Input")
	class UInputMappingContext* IMC_Player;

	UPROPERTY(EditAnywhere, Category="Input")
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Bomb;

	UPROPERTY(EditAnywhere, Category="Bomb")
	TSubclassOf<class ABomb> BombFactory;
	UPROPERTY(EditAnywhere, Category="Bomb")
	class ABomb* Bomb;
	UPROPERTY(EditAnywhere, Category="Bomb")
	TSubclassOf<class AStunBomb> StunBombFactory;
	class AStunBomb* StunBomb;

	UPROPERTY()
	TArray<class AGridTile*> GridTiles;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void SpawnBomb();
	UFUNCTION()
	void Stun();
	UFUNCTION()
	void SpawnStunBomb();

	UFUNCTION()
	class AGridTile* FindNearstTile(FVector Origin, const TArray<class AGridTile*>& TilesToCheck, float& Distance);
};
