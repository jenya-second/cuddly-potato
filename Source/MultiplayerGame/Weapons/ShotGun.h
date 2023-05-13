// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultWeapon.h"
#include "ShotGun.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AShotGun : public ADefaultWeapon
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotGun")
	float Angle;

	virtual void PressShoot() override;
	virtual void PressAlternativeShoot() override;
	void SetCanFireTrue();
	virtual void UnPressShoot() override;
	virtual void UnPressAlternativeShoot() override;
	virtual void MulticastSpawnBullet_Implementation(FTransform SpawnTransform) override;

	FTimerHandle ResetHandle;
};
