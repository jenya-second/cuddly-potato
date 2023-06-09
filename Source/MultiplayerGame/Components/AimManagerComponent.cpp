// Fill out your copyright notice in the Description page of Project Settings.


#include "AimManagerComponent.h"
#include "MultiplayerGame/Other/DefaultCharacter.h"


UAimManagerComponent::UAimManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	XOffset = 0;
	YOffset = 0;
	ZOffset = 0;
}


void UAimManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UAimManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	ADefaultCharacter* Ch = Cast<ADefaultCharacter>(GetOwner());
	if (Ch != nullptr) {
		ADefaultWeapon* Weapon = Ch->WeaponManager->CurrentWeapon;
		if (Weapon != nullptr) {
			FRotator CameraRot = Ch->Camera->GetComponentRotation();
			FVector Start = Ch->Camera->GetComponentLocation();
			FVector loc = CameraRot.Vector() * 60 + Start;
			FVector B = CameraRot.RotateVector(FVector(XOffset, YOffset, ZOffset));
			loc += B;
			Weapon->SetActorLocation(loc);
			FVector End = CameraRot.Vector() * 2000 + Start;
			FVector rot = End - Weapon->GetActorLocation();
			Weapon->SetActorRotation(rot.Rotation());
		}
	}
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true);
	// RV_TraceParams.bReturnPhysicalMaterial = false;
	// RV_TraceParams.AddIgnoredActor(GetOwner());
	// RV_TraceParams.AddIgnoredActor(Cast<AGamePersonCharacter>(GetOwner())->WeaponManager->CurrentWeapon);
	// FHitResult RV_Hit(ForceInit);
	// GetWorld()->LineTraceSingleByChannel(
	// RV_Hit,		
	// Start,
	// End,
	// ECC_Pawn,
	// RV_TraceParams);
	
	
}

