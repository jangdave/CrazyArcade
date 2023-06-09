// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyBox.generated.h"

UCLASS()
class CRAZYARCADE_API ADestroyBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	class UStaticMeshComponent* meshComp;

	UFUNCTION(Server, Unreliable)
	void DestroyBox();

	UFUNCTION(NetMulticast, Unreliable)
	void MultiDestroyBox();

	UPROPERTY(EditDefaultsOnly, Category = "Emitter")
	class UParticleSystem* destroyEmitter;

	virtual void Destroyed() override;
};
