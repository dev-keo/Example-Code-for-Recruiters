// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TH_GameMode.generated.h"

UCLASS()
class THIRTEENHEROES_API ATH_GameMode : public AGameMode
{
	GENERATED_BODY()

public: // Functions

	AActor* SpawnFlower(const FVector& Location, const bool& bUsePot);

protected: // Functions

	virtual void BeginPlay() override;

private: // Properties

	UPROPERTY(EditDefaultsOnly, Category = "TH")
	TSubclassOf<AActor> FlowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "TH")
	TSubclassOf<AActor> FlowerPotClass;
	
};
