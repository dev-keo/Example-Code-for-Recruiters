// Fill out your copyright notice in the Description page of Project Settings.


#include "TH_FunctionLibrary.h"

#include "EngineUtils.h"

#include "Actors/Casket.h"

float UTH_FunctionLibrary::AngleBetween(const FVector& A, const FVector& B)
{
	return FMath::Acos(Dot(A.GetSafeNormal(), B.GetSafeNormal())) * (180.f / PI);
}

float UTH_FunctionLibrary::Dot(const FVector& A, const FVector& B)
{
	return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}

TArray<ACasket*> UTH_FunctionLibrary::GetCaskets(UObject* WorldContextObject)
{
	TArray<ACasket*> Caskets;
	for (ACasket* const Casket : TActorRange<ACasket>(WorldContextObject ? WorldContextObject->GetWorld() : nullptr))
	{
		Caskets.Add(Casket);
	}
	return Caskets;
}

bool UTH_FunctionLibrary::AreAllCasketsCovered(UObject* WorldContextObject)
{
	for (ACasket* const Casket : GetCaskets(WorldContextObject))
	{
		if (!Casket->IsFullyCovered())
		{
			return false;
		}
	}
	return true;
}

