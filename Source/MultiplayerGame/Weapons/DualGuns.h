#pragma once

#include "CoreMinimal.h"
#include "DefaultWeapon.h"
#include "DualGuns.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API ADualGuns : public ADefaultWeapon
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotGun")
	bool CanFire = true;
	void SetCanFireTrue();
	virtual void PressShoot() override;
	virtual void PressAlternativeShoot() override;
	virtual void UnPressShoot() override;
	virtual void UnPressAlternativeShoot() override;
	virtual void MulticastSpawnBullet_Implementation(FTransform SpawnTransform) override;

	FTimerHandle ResetHandle;
};
