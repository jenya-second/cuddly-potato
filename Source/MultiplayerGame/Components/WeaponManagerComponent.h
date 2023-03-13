// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <MultiplayerGame/Weapons/DefaultWeapon.h>
#include "Net/UnrealNetwork.h"

#include "WeaponManagerComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERGAME_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManagerComponent();

	/*UPROPERTY(Replicated,EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	ADefaultWeapon* FPPCurrentWeapon;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	ADefaultWeapon* TPPCurrentWeapon;*/

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	int32 IndexWeapon = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<ADefaultWeapon*> FPPWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<ADefaultWeapon*> TPPWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<TSubclassOf<ADefaultWeapon>> WeaponsClasses;

	UFUNCTION()
	void SetCurrentWeapon(int32 Index);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetCurrentWeapon(int32 Index);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
