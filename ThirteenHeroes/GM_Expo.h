// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TH_GameMode.h"
#include "GM_Expo.generated.h"

UCLASS()
class THIRTEENHEROES_API AGM_Expo : public ATH_GameMode
{
	GENERATED_BODY()

protected: // Functions

	virtual void BeginPlay() override;

private: // Functions

	UFUNCTION()
	void UncoverCaskets(class ACasket* CasketCoveredLast);
	
};
