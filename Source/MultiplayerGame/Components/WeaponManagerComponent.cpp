#include "WeaponManagerComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UWeaponManagerComponent::ClientSetCurrentWeapon_Implementation(ADefaultWeapon* CurWeapon)
{
	Weapons.Add(CurWeapon);
}

void UWeaponManagerComponent::NetSetWeapon_Implementation()
{
	bool another=false;
	if (Weapons.Num() != WeaponsClasses.Num()) {
		another = true;
	}
	ADefaultCharacter* Ch = Cast<ADefaultCharacter>(GetOwner());
	for (int i = 0; i < Weapons.Num(); i++) {
		if (!IsValid(Weapons[i])) {
			another = true;
			break;
		}
	}
	if (another) {
		FTimerHandle UnusedHandle;
		Ch->GetWorldTimerManager().SetTimer(UnusedHandle,
			this, &UWeaponManagerComponent::NetSetWeapon, 0.1, false, 0.1);
		UE_LOG(LogTemp, Warning, TEXT("Another one"));
		return;
	}
	for (int i = 0; i < Weapons.Num(); i++) {
		if (Ch != nullptr) {
			if (Ch->GetLocalRole() == ROLE_Authority) {
				Weapons[i]->AttachToComponent(Ch->Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			}
			else {
				if (UGameplayStatics::GetPlayerPawn(GetWorld(), 0) == GetOwner() || Ch->Controller) {
					Weapons[i]->AttachToComponent(Ch->Arms, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Right_arm");
				}
				else {
					Weapons[i]->AttachToComponent(Ch->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Right_arm");
				}
			}
		}
	}
}

void UWeaponManagerComponent::NetSetCurrentWeapon(int Index)
{
	ADefaultCharacter* Ch = Cast<ADefaultCharacter>(GetOwner());
	bool another = false;
	if (Weapons.Num() != WeaponsClasses.Num()) {
		another = true;
	}
	for (int i = 0; i < Weapons.Num(); i++) {
		if (!IsValid(Weapons[i])) {
			another = true;
			break;
		}
	}
	if (another) {
		FTimerHandle UnusedHandle;
		FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUFunction(this, FName("NetSetCurrentWeapon"), Index);
		Ch->GetWorldTimerManager().SetTimer(UnusedHandle, RespawnDelegate, 0.1, false, 0.1);
		UE_LOG(LogTemp, Warning, TEXT("Another one"));
		return;
	}
	Weapons[IndexWeapon]->SetActorHiddenInGame(true);
	IndexWeapon = Index;
	Weapons[IndexWeapon]->SetActorHiddenInGame(false);

}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	Weapons.Empty();
	ADefaultCharacter* Ch = Cast<ADefaultCharacter>(GetOwner());
	for (int i = 0; i < WeaponsClasses.Num(); i++)
	{	
		FTransform SpawnTransform = Cast<ADefaultCharacter>(GetOwner())->Camera->GetComponentTransform();
		if (Ch->GetLocalRole() == ROLE_Authority) {
			CurrentWeapon = Cast<ADefaultWeapon>(GetWorld()->SpawnActor(WeaponsClasses[i], &SpawnTransform));
			CurrentWeapon->SetActorHiddenInGame(true);
			CurrentWeapon->SetOwner(GetOwner());
			ClientSetCurrentWeapon(CurrentWeapon);
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
	NetSetCurrentWeapon(Index);
}

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponManagerComponent, IndexWeapon);
	DOREPLIFETIME(UWeaponManagerComponent, CurrentWeapon);
	DOREPLIFETIME(UWeaponManagerComponent, Weapons);
}

