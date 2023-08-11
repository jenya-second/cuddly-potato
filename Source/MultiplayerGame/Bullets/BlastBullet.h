#pragma once

#include "CoreMinimal.h"
#include "DefaultBullet.h"
#include "BlastBullet.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API ABlastBullet : public ADefaultBullet
{
	GENERATED_BODY()
public:
	virtual void NotifyActorBeginOverlap(AActor* Actor) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Radius;
};
