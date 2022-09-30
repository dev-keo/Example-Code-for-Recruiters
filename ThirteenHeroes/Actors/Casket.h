// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "../TH_GameInstance.h"
#include "Casket.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCovered, class ACasket*, Casket);

UCLASS()
class THIRTEENHEROES_API ACasket : public AInteractableActor
{
	GENERATED_BODY()
	
public: // Functions

	ACasket();

	virtual void OnInteracted_Implementation(class ATH_Player* Player) override;
	void Cover(class ATH_Player* Player);
	void Uncover();

	UFUNCTION(BlueprintCallable, Category = "TH|Components")
	void SetFlag(UStaticMeshComponent* InComp);

	UFUNCTION(BlueprintCallable, Category = "TH|Components")
	void SetHeadstoneSpawnPoint(USceneComponent* InComp);

	bool IsFullyCovered() const;

public: // Properties

	UPROPERTY()
	FOnCovered OnCovered;

protected: // Functions

	virtual void BeginPlay() override;

protected: // Properties

	UStaticMeshComponent* Flag = nullptr;
	USceneComponent* HeadstoneSpawnPoint = nullptr;

private: // Functions

	void SpawnHeadstone();

private: // Properties

	bool bIsFullyCovered = false;

	UPROPERTY(EditDefaultsOnly, Category = "TH")
	TArray<UStaticMesh*> StraightenedFlags;

	UStaticMesh* UnstraightenedFlag = nullptr;

	// @warning Needs to be valid index for SoldiersInfo array in UTH_GameInstance
	UPROPERTY(EditInstanceOnly, meta = (ClampMin = "0"), Category = "TH")
	int32 SoldierIndex;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "TH")
	FSoldierInfo SoldierInfo;

	UPROPERTY(EditDefaultsOnly, Category = "TH")
	TSubclassOf<AActor> HeadstoneClass;

};
