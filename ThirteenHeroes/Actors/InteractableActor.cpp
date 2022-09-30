// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"

#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

#include "../TH_PlayerController.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);
}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	if (CollisionComp)
	{
		CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnBeginOverlap);
		CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::OnEndOverlap);
	}
}

void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetPromptColor(IsTarget() ? FColor::Green : FColor::White);
}

void AInteractableActor::OnInteracted_Implementation(ATH_Player* Player) {}

void AInteractableActor::SetInteractPromptComp(UWidgetComponent* InComp)
{
	InteractPromptComp = InComp;
}

void AInteractableActor::SetCollisionComp(UBoxComponent* InComp)
{
	CollisionComp = InComp;
}

void AInteractableActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetPromptVisibility(true);
}

void AInteractableActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetPromptVisibility(false);
}

void AInteractableActor::SetPromptVisibility_Implementation(bool bShowPrompt)
{
	SetActorTickEnabled(bShowPrompt);
}

bool AInteractableActor::IsTarget() const
{
	ATH_PlayerController* const PC = GetWorld()->GetFirstPlayerController<ATH_PlayerController>();
	return PC ? PC->LookForward().GetActor() == this : false;
}

