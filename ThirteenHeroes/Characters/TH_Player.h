// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TH_Player.generated.h"

UCLASS()
class THIRTEENHEROES_API ATH_Player : public ACharacter
{
	GENERATED_BODY()

public: // Functions
	
	ATH_Player();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ReceiveFlower();

protected: // Functions
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "TH|Flower")
	void UpdateFlowerCount(int32 Count);

	UFUNCTION(BlueprintPure, Category = "TH|Flower")
	bool CanPlantFlower(FVector& OutLocation, bool& bOutIsSurfacePlantable) const;

protected: // Properties

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0"), BlueprintReadOnly, Category = "TH|Movement")
	float WalkSpeed = 300.f;

	// Always greater than or equal to WalkSpeed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TH|Movement")
	float RunSpeed = 600.f;

private: // Functions

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_ToggleRun();
	void Server_ToggleRun_Implementation();
	bool Server_ToggleRun_Validate();

	UFUNCTION()
	void OnRep_bIsRunning();

	void PlantFlower();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SpawnFlower(FVector_NetQuantize Location, bool bUsePot);
	void Server_SpawnFlower_Implementation(FVector_NetQuantize Location, bool bUsePot);
	bool Server_SpawnFlower_Validate(FVector_NetQuantize Location, bool bUsePot);

	void Interact();

private: // Properties

	UPROPERTY(ReplicatedUsing = "OnRep_bIsRunning")
	bool bIsRunning = false;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Flower")
	TArray<TEnumAsByte<EPhysicalSurface>> PlantableSurfaces;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Flower")
	TArray<TEnumAsByte<EPhysicalSurface>> PotPlaceableSurfaces;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0"), Category = "TH|Flower")
	int32 FlowerCount;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0"), Category = "TH|Flower")
	float AngleTolerance = 5.f;

};
