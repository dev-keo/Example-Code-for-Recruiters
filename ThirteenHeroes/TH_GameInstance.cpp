// Fill out your copyright notice in the Description page of Project Settings.


#include "TH_GameInstance.h"

FSoldierInfo UTH_GameInstance::GetInfo(const int32& Index) const
{
	return SoldiersInfo[Index];
}

