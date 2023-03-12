// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletManagerComponent.h"

// Sets default values for this component's properties
UBulletManagerComponent::UBulletManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
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


// Called every frame
void UBulletManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

