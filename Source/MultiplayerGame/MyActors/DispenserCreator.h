#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DispenserCreator.generated.h"

class ADefaultBullet;
class UCapsuleComponent;
class ADispenser;

UCLASS()
class MULTIPLAYERGAME_API ADispenserCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	ADispenserCreator();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DispenserCreator")
	UStaticMeshComponent* DispenserCreatorBody;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DispenserCreator")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DispenserCreator")
	float CreatingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DispenserCreator")
	TArray<TSubclassOf<ADefaultBullet>> BulletClasses;
	FTimerHandle ResetHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DispenserCreator")
	TSubclassOf<ADispenser> DispenserClass;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void StartCreating();
	void StopCreating();
	void CreateRandomDespenser();
	void CreateDespenser(TSubclassOf<ADefaultBullet> BulletClass);

};
