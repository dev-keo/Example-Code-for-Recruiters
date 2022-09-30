// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

UCLASS()
class THIRTEENHEROES_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public: // Functions
	
	AInteractableActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "TH|Interact")
	void OnInteracted(class ATH_Player* Player);
	virtual void OnInteracted_Implementation(class ATH_Player* Player);

	UFUNCTION(BlueprintCallable, Category = "TH|Components")
	void SetInteractPromptComp(class UWidgetComponent* InComp);

	UFUNCTION(BlueprintCallable, Category = "TH|Components")
	void SetCollisionComp(class UBoxComponent* InComp);

protected: // Functions
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "TH|Interact")
	void SetPromptVisibility(bool bShowPrompt);
	virtual void SetPromptVisibility_Implementation(bool bShowPrompt);

	UFUNCTION(BlueprintImplementableEvent, Category = "TH|Interact")
	void SetPromptColor(FLinearColor Color);

protected: // Properties

	class UWidgetComponent* InteractPromptComp = nullptr;
	class UBoxComponent* CollisionComp = nullptr;

private: // Functions

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Returns if the Actor is in the player's line of sight
	bool IsTarget() const;

};
