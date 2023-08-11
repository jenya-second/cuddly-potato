#pragma once

#include "CoreMinimal.h"
#include "DefaultWeapon.h"
#include <Components/TimelineComponent.h>
#include "Bow.generated.h"


/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API ABow : public ADefaultWeapon
{
	GENERATED_BODY()
public:
	ABow();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* TimeLine;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	UCurveFloat* Curve;
	UFUNCTION()
	void EffectProgress(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float PullKoef;

	FTimerHandle ResetHandle;
	FTimerHandle SetCanFireHandle;
	void BotShoot() override;
	void PrepareToShoot();
	void SetCanFireTrue();
	UFUNCTION(BlueprintCallable)
	virtual void PressShoot() override;
	virtual void PressAlternativeShoot() override;
	virtual void UnPressShoot() override;
	virtual void UnPressAlternativeShoot() override;
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSpawnArrow(FTransform SpawnTransform, float Koef);
protected:
	virtual void BeginPlay() override;
	/*void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;*/
};
