// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include <MultiplayerGame/Components/AimManagerComponent.h>
#include <MultiplayerGame/Components/WeaponManagerComponent.h>
#include <MultiplayerGame/Components/BulletManagerComponent.h>
#include "DefaultCharacter.generated.h"


UCLASS()
class MULTIPLAYERGAME_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADefaultCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "aa")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "aa")
	UWeaponManagerComponent* WeaponManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "aa")
	UBulletManagerComponent* BulletManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "aa")
	UAimManagerComponent* AimManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "aa")
	USkeletalMeshComponent* Arms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "aa")
	float MaxHelth=100;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, EditAnywhere, BlueprintReadWrite, Category = "aa")
	float CurrentHealth;

	UPROPERTY(ReplicatedUsing = OnRep_Color, EditAnywhere, BlueprintReadWrite, Category = "aa")
	FColor Color;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "aa")
	float Shield = 0;

	UFUNCTION()
	void OnRep_CurrentHealth();
	UFUNCTION()
	void OnRep_Color();

	void SetMat(FColor Col);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Destroyed() override;
	virtual void UnPossessed() override;
	virtual void PossessedBy(AController* NewController) override;

	FTimerHandle ForShoot;
	FTimerHandle ForAlternativeShoot;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float X);
	void MoveSide(float X);
	void LookRight(float X);
	void LookUp(float X);
	void StartJump();
	void StopJump();
	void DestroyWeapons();
	UFUNCTION(BlueprintCallable)
	void OnMenu();
	void OnStatsReleased();
	void OnStatsPressed();
	UFUNCTION(NetMulticast, Unreliable)
	void OnDead();
	UFUNCTION(Server, Unreliable)
	void NextWeapon();
	UFUNCTION(Server, Unreliable)
	void NextBullet();
	UFUNCTION(Server, Reliable)
	void PressShoot();
	UFUNCTION(Server, Reliable)
	void UnPressShoot();
	UFUNCTION(Server, Reliable)
	void PressAlternativeShoot();
	UFUNCTION(Server, Reliable)
	void UnPressAlternativeShoot();
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastUpdateCameraView(FRotator rot);

private:
	TArray<FInputActionBinding> AcBind;
	TArray<FInputAxisBinding> AxBind;

	
};
