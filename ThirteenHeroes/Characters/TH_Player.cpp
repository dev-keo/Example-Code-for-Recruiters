// Fill out your copyright notice in the Description page of Project Settings.


#include "TH_Player.h"

#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "../TH_PlayerController.h"
#include "../TH_GameMode.h"
#include "../TH_FunctionLibrary.h"

ATH_Player::ATH_Player()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATH_Player::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATH_Player, bIsRunning);
}

void ATH_Player::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->SetGenerateOverlapEvents(IsLocallyControlled());
	RunSpeed = FMath::Max(WalkSpeed, RunSpeed);
	OnRep_bIsRunning();
}

void ATH_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("ToggleRun"), EInputEvent::IE_Pressed, this, &ATH_Player::Server_ToggleRun);
	PlayerInputComponent->BindAction(TEXT("PlantFlower"), IE_Pressed, this, &ATH_Player::PlantFlower);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ATH_Player::Interact);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATH_Player::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATH_Player::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACharacter::AddControllerPitchInput);
}

void ATH_Player::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ATH_Player::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ATH_Player::Server_ToggleRun_Implementation()
{
	bIsRunning = !bIsRunning;
	OnRep_bIsRunning();
}

bool ATH_Player::Server_ToggleRun_Validate() { return true; }

void ATH_Player::OnRep_bIsRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? RunSpeed : WalkSpeed;
}

void ATH_Player::PlantFlower()
{
	FVector Location;
	bool bIsSurfacePlantable;
	if (CanPlantFlower(Location, bIsSurfacePlantable))
	{
		Server_SpawnFlower(Location, /*bUsePot=*/!bIsSurfacePlantable);
		UpdateFlowerCount(--FlowerCount);
	}
}

bool ATH_Player::CanPlantFlower(FVector& OutLocation, bool& bOutIsSurfacePlantable) const
{
	ATH_PlayerController* const PC = GetController<ATH_PlayerController>();
	if (FlowerCount > 0 && PC)
	{
		const FHitResult Hit = PC->LookForward(/*ReachDistance=*/200.f);
		OutLocation = Hit.ImpactPoint;
		if (Hit.PhysMaterial.IsValid())
		{
			bOutIsSurfacePlantable = PlantableSurfaces.Contains(Hit.PhysMaterial->SurfaceType);
			const bool bIsSurfacePotPlaceable = PotPlaceableSurfaces.Contains(Hit.PhysMaterial->SurfaceType);
			const bool bIsSurfaceFlat = UKismetMathLibrary::NearlyEqual_FloatFloat(UTH_FunctionLibrary::AngleBetween(Hit.ImpactNormal, FVector::UpVector), 0.f, AngleTolerance);
			return (bOutIsSurfacePlantable || bIsSurfacePotPlaceable) && bIsSurfaceFlat;
		}
	}
	return false;
}

void ATH_Player::Server_SpawnFlower_Implementation(FVector_NetQuantize Location, bool bUsePot)
{
	if (ATH_GameMode* const GM = GetWorld()->GetAuthGameMode<ATH_GameMode>())
	{
		GM->SpawnFlower(Location, bUsePot);
	}
}

bool ATH_Player::Server_SpawnFlower_Validate(FVector_NetQuantize Location, bool bUsePot) { return true; }

void ATH_Player::Interact()
{
	if (ATH_PlayerController* const PC = GetController<ATH_PlayerController>())
	{
		PC->Interact();
	}
}

void ATH_Player::ReceiveFlower()
{
	UpdateFlowerCount(++FlowerCount);
}

