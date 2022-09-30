// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Expo.h"

#include "TH_FunctionLibrary.h"
#include "Actors/Casket.h"

void AGM_Expo::BeginPlay()
{
	Super::BeginPlay();
	for (ACasket* const Casket : UTH_FunctionLibrary::GetCaskets(GetWorld()))
	{
		Casket->OnCovered.AddDynamic(this, &AGM_Expo::UncoverCaskets);
	}
}

void AGM_Expo::UncoverCaskets(ACasket* CasketCoveredLast)
{
	if (UTH_FunctionLibrary::AreAllCasketsCovered(GetWorld()))
	{
		for (ACasket* const Casket : UTH_FunctionLibrary::GetCaskets(GetWorld()))
		{
			if (Casket != CasketCoveredLast)
			{
				Casket->Uncover();
			}
		}
	}
}

