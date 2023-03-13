// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineGun.h"
#include "MultiplayerGame/Components/BulletManagerComponent.h"
#include "MultiplayerGame/Components/WeaponManagerComponent.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

void AMachineGun::PressShoot()
{
	ADefaultCharacter* PlayerOwner = Cast<ADefaultCharacter>(GetOwner());
	if (PlayerOwner != nullptr) {
		if (CanFire && PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet] > 0 && CurrentCharge >= 1)
		{
			const FTransform SpawnTransform = WeaponBody->GetSocketTransform("For_bullet");
			ADefaultBullet* Actor = Cast<ADefaultBullet>(GetWorld()->SpawnActor(PlayerOwner->BulletManager->CurrentBullet, &SpawnTransform));
			if (Actor != nullptr) {
				Actor->BulletBody->SetPhysicsLinearVelocity(SpawnTransform.Rotator().Vector() *
					Actor->Speed *
					BulletSpeedScale);
				Actor->SetOwner(PlayerOwner);
			}
			CanFire = false;
			PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet]--;
			CurrentCharge--;
		}
		if (!GetWorldTimerManager().IsTimerActive(ResetHandle))
		{
			{
				GetWorldTimerManager().SetTimer(ResetHandle, this, &AMachineGun::SetCanFireTrue, FireSpeed, false);
			}
		}
	}
	


}

void AMachineGun::PressAlternativeShoot()
{

}

void AMachineGun::SetCanFireTrue()
{
	CanFire = true;
}

void AMachineGun::UnPressShoot()
{

}

void AMachineGun::UnPressAlternativeShoot()
{

}

void AMachineGun::BeginPlay()
{
	Super::BeginPlay();
}

void AMachineGun::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurrentCharge < MaxCharge)
	{
		CurrentCharge += DeltaSeconds * ChargingSpeed;
	}
}