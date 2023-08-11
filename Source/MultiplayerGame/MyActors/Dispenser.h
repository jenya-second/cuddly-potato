#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dispenser.generated.h"

class ADefaultBullet;
class UCapsuleComponent;

UCLASS()
class MULTIPLAYERGAME_API ADispenser : public AActor
{
	GENERATED_BODY()
	
public:	
	ADispenser();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dispenser")
	UStaticMeshComponent* DispenserBody;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dispenser")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dispenser")
	TSubclassOf<ADefaultBullet> BulletClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dispenser")
	int32 NumOfBullets;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* Actor) override;

};
