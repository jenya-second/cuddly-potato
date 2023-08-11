// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/CapsuleComponent.h>
#include "DefaultWeapon.generated.h"


UCLASS()
class MULTIPLAYERGAME_API ADefaultWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultWeapon();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	bool CanFire = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float CheckRadius = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float TargetDistance = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	UStaticMeshComponent* WeaponBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Ammo")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float FireSpeed=1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float BulletSpeedScale=1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float BulletDamageScale=1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	bool bIsAutomatic = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float LinearDamp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(NetMulticast,Unreliable)
	virtual void MulticastSpawnBullet(FTransform SpawnTransform);

	virtual void PressShoot();
	virtual void UnPressShoot();
	virtual void PressAlternativeShoot();
	virtual void UnPressAlternativeShoot();

	UFUNCTION(BlueprintCallable)
	virtual void BotShoot();
};
