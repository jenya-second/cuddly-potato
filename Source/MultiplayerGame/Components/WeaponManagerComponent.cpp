// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManagerComponent.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

// Sets default values for this component's properties
UWeaponManagerComponent::UWeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	Weapons.Empty();
	for (int i = 0; i < WeaponsClasses.Num(); i++)
	{
		const FTransform* SpawnTransform = &GetOwner()->GetActorTransform();
		// UE_LOG(LogTemp,Warning,TEXT("Spawned"));
		Weapons.Add(Cast<ADefaultWeapon>(GetWorld()->SpawnActor(WeaponsClasses[i], SpawnTransform)));
		Weapons[i]->SetActorHiddenInGame(true);
		Weapons[i]->SetOwner(GetOwner());
		ADefaultCharacter* Ch = Cast<ADefaultCharacter>(GetOwner());
		if (Ch != nullptr) {
			Weapons[i]->AttachToComponent(Ch->Arms, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Right_arm");
		}
	}
	SetCurrentWeapon(0);
	
}

void UWeaponManagerComponent::SetCurrentWeapon_Implementation(int32 Index)
{
	if (Index >= 0 && Index < Weapons.Num())
	{
		if (CurrentWeapon != nullptr)
		{
			CurrentWeapon->SetActorHiddenInGame(true);
		}
		CurrentWeapon = Weapons[Index];
		CurrentWeapon->SetActorHiddenInGame(false);
		IndexWeapon = Index;
	}

}

// Called every frame
void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponManagerComponent,CurrentWeapon);
}

