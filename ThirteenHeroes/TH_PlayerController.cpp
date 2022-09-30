// Fill out your copyright notice in the Description page of Project Settings.


#include "TH_PlayerController.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Actors/InteractableActor.h"
#include "Characters/TH_Player.h"

FHitResult ATH_PlayerController::LookForward(float ReachDistance, bool bDrawDebug)
{
	FHitResult Hit;

	FVector Start;
	FRotator LookDirection;
	GetPlayerViewPoint(Start, LookDirection);
	const FVector End = Start + (LookDirection.Vector() * ReachDistance);

	TArray<AActor*> ActorsToIgnore;
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
		/*bTraceComplex=*/false,
		ActorsToIgnore,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		Hit,
		/*bIgnoreSelf=*/true
	);
	return Hit;
}

void ATH_PlayerController::Interact()
{
	if (AInteractableActor* const InteractableActor = Cast<AInteractableActor>(LookForward().GetActor()))
	{
		InteractableActor->OnInteracted(GetPawn<ATH_Player>());
	}
}

