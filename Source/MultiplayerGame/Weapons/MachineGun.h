// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultWeapon.h"
#include "MachineGun.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AMachineGun : public ADefaultWeapon
{
	GENERATED_BODY()
public:
	
	virtual void PressShoot() override;
	virtual void PressAlternativeShoot() override;
	void SetCanFireTrue();
	virtual void UnPressShoot() override;
	virtual void UnPressAlternativeShoot() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MashineGun")
	float MaxCharge = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MashineGun")
	float CurrentCharge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MashineGun")
	float ChargingSpeed = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MashineGun")
	bool CanFire = true;
	FTimerHandle ResetHandle;
};
