#include "WeaponManagerComponent.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

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

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponManagerComponent,CurrentWeapon);
}

