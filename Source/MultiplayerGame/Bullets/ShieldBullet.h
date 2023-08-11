#pragma once

#include "CoreMinimal.h"
#include "DefaultBullet.h"
#include "ShieldBullet.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AShieldBullet : public ADefaultBullet
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void DoDamage(AActor* Actor) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float ShieldKoef;
};
