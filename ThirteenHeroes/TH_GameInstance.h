// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TH_GameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSoldierInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name = TEXT("Name");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Branch = TEXT("Branch");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Birthplace = TEXT("Birthplace");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTexture2D*> Pictures;
};

UCLASS()
class THIRTEENHEROES_API UTH_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public: // Functions

	FSoldierInfo GetInfo(const int32& Index) const;

private: // Properties

	UPROPERTY(EditDefaultsOnly, Category = "TH")
	TArray<FSoldierInfo> SoldiersInfo;
	
};
