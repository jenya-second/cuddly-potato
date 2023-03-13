#include "WeaponManagerComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	FPPWeapons.Empty();
	TPPWeapons.Empty();
	for (int i = 0; i < WeaponsClasses.Num(); i++)
	{
		FTransform SpawnTransform = Cast<ADefaultCharacter>(GetOwner())->Camera->GetComponentTransform();
		FPPWeapons.Add(Cast<ADefaultWeapon>(GetWorld()->SpawnActor(WeaponsClasses[i],&SpawnTransform)));
		FPPWeapons[i]->SetActorHiddenInGame(true);
		FPPWeapons[i]->SetOwner(GetOwner());
		TPPWeapons.Add(Cast<ADefaultWeapon>(GetWorld()->SpawnActor(WeaponsClasses[i], &SpawnTransform)));
		TPPWeapons[i]->SetActorHiddenInGame(true);
		TPPWeapons[i]->SetOwner(GetOwner());
		ADefaultCharacter* Ch = Cast<ADefaultCharacter>(GetOwner());
		if (Ch != nullptr) {
			if (Ch->GetLocalRole() == ROLE_Authority) {
				FPPWeapons[i]->AttachToComponent(Ch->Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			}
			else{
				FPPWeapons[i]->AttachToComponent(Ch->Arms, FAttachmentTransformRules::SnapToTargetNotIncludingScale,"Right_arm");
			}
			TPPWeapons[i]->AttachToComponent(Ch->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Right_arm");
		}
	}
}

void UWeaponManagerComponent::SetCurrentWeapon(int32 Index)
{
	if (Index >= 0 && Index < WeaponsClasses.Num())
	{
		MulticastSetCurrentWeapon(Index);
	}
}

void UWeaponManagerComponent::MulticastSetCurrentWeapon_Implementation(int32 Index)
{
	ADefaultCharacter* ch = Cast<ADefaultCharacter>(GetOwner());
	if (!ch) {
		return;
	}
	if (FPPWeapons[IndexWeapon]){
		FPPWeapons[IndexWeapon]->SetActorHiddenInGame(true);
	}
	if (TPPWeapons[IndexWeapon]) {
		TPPWeapons[IndexWeapon]->SetActorHiddenInGame(true);
	}
	IndexWeapon = Index;
	if (UGameplayStatics::GetPlayerPawn(GetWorld(),0) == GetOwner() || ch->Controller) {
		if (FPPWeapons[IndexWeapon]) {
			FPPWeapons[IndexWeapon]->SetActorHiddenInGame(false);
		}
		
	}
	else {
		if (TPPWeapons[IndexWeapon]) {
			TPPWeapons[IndexWeapon]->SetActorHiddenInGame(false);
		}
		
	}
}

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponManagerComponent, IndexWeapon);
}

