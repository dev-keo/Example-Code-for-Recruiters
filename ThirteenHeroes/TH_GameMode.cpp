// Fill out your copyright notice in the Description page of Project Settings.


#include "TH_GameMode.h"

void ATH_GameMode::BeginPlay()
{
	Super::BeginPlay();
}

AActor* ATH_GameMode::SpawnFlower(const FVector& Location, const bool& bUsePot)
{
	const FRotator Rotation = FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f);
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor(bUsePot ? FlowerPotClass.Get() : FlowerClass.Get(), &Location, &Rotation, Params);
}

