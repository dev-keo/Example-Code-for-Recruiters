// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TH_PlayerController.generated.h"

UCLASS()
class THIRTEENHEROES_API ATH_PlayerController : public APlayerController
{
	GENERATED_BODY()

public: // Functions

	UFUNCTION(BlueprintCallable, Category = "TH")
	FHitResult LookForward(float ReachDistance = 150.f, bool bDrawDebug = false);

	UFUNCTION(BlueprintCallable, Category = "TH")
	void Interact();
	
};
