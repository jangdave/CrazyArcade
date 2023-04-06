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

	UFUNCTION(Client, Unreliable)
	void ClientSpawnBomb();
	UFUNCTION(Server, Unreliable)
	void ServerSpawnBomb();

	UFUNCTION(Client, Unreliable)
	void ClientStun();
	UFUNCTION(Server, Unreliable)
	void ServerStun();
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastStun();
	UFUNCTION()
	void SpawnStunBomb();

	UFUNCTION()
	class AGridTile* FindNearstTile(FVector Origin, const TArray<class AGridTile*>& TilesToCheck, float& Distance);

	UPROPERTY()
	bool bIsDead = false;
	UPROPERTY()
	FString Text_IfWin = "";


	// 이름 저장
	UFUNCTION(Server, Unreliable)
	void ServerSetName(const FString& name);

	UPROPERTY(Replicated)
	FString pName;

	// 색상 변환
	UPROPERTY(Replicated)
	class UMaterialInstanceDynamic* mat1;

	UPROPERTY(Replicated)
	class UMaterialInstanceDynamic* mat2;

	UFUNCTION(Server, Unreliable)
	void ServerSetColor(const FVector& color);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSetColor(const FVector& color);

	class UCrazyGameInstance* gameInstance;
	
	class AStartWidgetController* startCont;

	UFUNCTION(Server, Unreliable)
	void ServerColor(const FVector& color, bool bCheck);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastColor(const FVector& color, bool bCheck);

	UPROPERTY(Replicated)
	bool bCheckReady;

	bool bOnce;

	class ACrazyGameStateBase* gs;

	// 세션 종료
	UFUNCTION()
	void KickPlayer(const FString& text);

	UFUNCTION()
	void EndSession();

	UFUNCTION()
	void DestroyGame();

	UFUNCTION()
	void EndGame();

	UFUNCTION(Server, Unreliable)
	void ServerDestroyGame();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastDestroyGame();
};
