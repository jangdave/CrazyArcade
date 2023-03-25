// Fill out your copyright notice in the Description page of Project Settings.


#include "BombEffect_Niagara.h"

#include "CrazyArcadePlayer.h"
#include "DestroyBox.h"
#include "FixBox.h"
#include "Kismet/GameplayStatics.h"

void UBombEffect_Niagara::OnBombPopBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<ACrazyArcadePlayer>(OtherActor);
	auto destroyBox = Cast<ADestroyBox>(OtherActor);
	auto fixBox = Cast<AFixBox>(OtherActor);


}
