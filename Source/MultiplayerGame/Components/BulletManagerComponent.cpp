#include "BulletManagerComponent.h"

UBulletManagerComponent::UBulletManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UBulletManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = CountBullets.Num(); i < BulletsClasses.Num(); i++)
	{
		CountBullets.Add(0);
	}
	if (BulletsClasses.Num() != 0)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("Shoot"));*/
		SetCurrentBullet(0);
	}
}

void UBulletManagerComponent::SetCurrentBullet(int32 Index)
{
	if (Index >= 0 && Index < BulletsClasses.Num())
	{
		CurrentBullet = BulletsClasses[Index];
		IndexBullet = Index;
	}
}

void UBulletManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBulletManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UBulletManagerComponent, CurrentBullet);
	DOREPLIFETIME(UBulletManagerComponent, CountBullets);
}

