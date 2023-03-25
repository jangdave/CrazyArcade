// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "BombEffect_Niagara.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYARCADE_API UBombEffect_Niagara : public UNiagaraComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Bomb")
	class UBoxComponent* BoxCollision;

	UFUNCTION()
	void OnBombPopBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
