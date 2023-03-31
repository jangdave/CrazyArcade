// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class CRAZYARCADE_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Bomb")
	class USphereComponent* SphereCollision;
	UPROPERTY(EditAnywhere, Category="Bomb")
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bomb")
	class UNiagaraComponent* BombParticlesVertical;
	UPROPERTY(EditAnywhere, Category="Bomb")
	class UBoxComponent* BombCollisionVertical;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bomb")
	class UNiagaraComponent*  BombParticlesHorizontal;
	UPROPERTY(EditAnywhere, Category = "Bomb")
	class UBoxComponent* BombCollisionHorizontal;

	UFUNCTION()
	void Pop();

	UFUNCTION()
	void OnBombPopBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
