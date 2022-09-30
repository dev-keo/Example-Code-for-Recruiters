// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TH_FunctionLibrary.generated.h"

UCLASS()
class THIRTEENHEROES_API UTH_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static float AngleBetween(const FVector& A, const FVector& B);

	static float Dot(const FVector& A, const FVector& B);

	static TArray<class ACasket*> GetCaskets(UObject* WorldContextObject);

	static bool AreAllCasketsCovered(UObject* WorldContextObject);
	
};
