// Fill out your copyright notice in the Description page of Project Settings.


#include "Casket.h"

#include "Components/BoxComponent.h"

#include "../Characters/TH_Player.h"

ACasket::ACasket()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACasket::BeginPlay()
{
	Super::BeginPlay();
	if (UTH_GameInstance* const GI = GetGameInstance<UTH_GameInstance>())
	{
		SoldierInfo = GI->GetInfo(SoldierIndex);
		SpawnHeadstone();
	}
	UnstraightenedFlag = Flag ? Flag->GetStaticMesh() : nullptr;
}

void ACasket::SpawnHeadstone()
{
	if (HeadstoneSpawnPoint)
	{
		const FTransform Transform = HeadstoneSpawnPoint->GetComponentTransform();
		FActorSpawnParameters Params;
		Params.Owner = this;
		GetWorld()->SpawnActor(HeadstoneClass.Get(), &Transform, Params);
	}
}

void ACasket::OnInteracted_Implementation(ATH_Player* Player)
{
	Cover(Player);
}

void ACasket::Cover(ATH_Player* Player)
{
	if (!bIsFullyCovered)
	{
		bIsFullyCovered = true;
		if (Flag)
		{
			const int32 RandIndex = FMath::RandRange(0, StraightenedFlags.Num() - 1);
			Flag->SetStaticMesh(StraightenedFlags[RandIndex]);
		}
		if (CollisionComp)
		{
			CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		SetPromptVisibility(false);
		if (Player)
		{
			Player->ReceiveFlower();
		}
		if (OnCovered.IsBound())
		{
			OnCovered.Broadcast(this);
		}
	}
}

void ACasket::Uncover()
{
	if (Flag)
	{
		Flag->SetStaticMesh(UnstraightenedFlag);
	}
	if (CollisionComp)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	bIsFullyCovered = false;
}

void ACasket::SetFlag(UStaticMeshComponent* InComp)
{
	Flag = InComp;
}

void ACasket::SetHeadstoneSpawnPoint(USceneComponent* InComp)
{
	HeadstoneSpawnPoint = InComp;
}

bool ACasket::IsFullyCovered() const
{
	return bIsFullyCovered;
}

