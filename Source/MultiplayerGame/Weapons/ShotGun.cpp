// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotGun.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

void AShotGun::PressShoot()
{
	ADefaultCharacter* PlayerOwner = Cast<ADefaultCharacter>(GetOwner());
	if (PlayerOwner != nullptr) {
		if (CanFire && PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet] >= 4)
		{
			const FTransform SpawnTransform = WeaponBody->GetSocketTransform("For_bullet");
			MulticastSpawnBullet(SpawnTransform);
			CanFire = false;
			PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet] -= 4;
		}
		if (!GetWorldTimerManager().IsTimerActive(ResetHandle))
		{
			GetWorldTimerManager().SetTimer(ResetHandle, this, &AShotGun::SetCanFireTrue, FireSpeed, false);
		}
	}
}

void AShotGun::PressAlternativeShoot()
{
}

void AShotGun::SetCanFireTrue()
{
	CanFire = true;
}

void AShotGun::UnPressShoot()
{
}

void AShotGun::UnPressAlternativeShoot()
{
}

void AShotGun::MulticastSpawnBullet_Implementation(FTransform SpawnTransform)
{
	ADefaultCharacter* PlayerOwner = Cast<ADefaultCharacter>(GetOwner());
	if (PlayerOwner != nullptr) {
		for (int i = 0; i < 16; i++) {
			ADefaultBullet* Actor = Cast<ADefaultBullet>(GetWorld()->SpawnActorDeferred<ADefaultBullet>(PlayerOwner->BulletManager->CurrentBullet, SpawnTransform, PlayerOwner));
			if (Actor != nullptr) {
				Actor->Damage *= BulletDamageScale;
				Actor->LinearDamping = LinearDamp;
				Actor->FinishSpawning(SpawnTransform);
				FVector vect = SpawnTransform.Rotator().Vector() *
					Actor->Speed * BulletSpeedScale;
				
				Actor->ProjectileComponent->Velocity = vect.RotateAngleAxis(FMath::FRandRange(0, Angle), FVector(FMath::FRandRange(0, 1), FMath::FRandRange(0, 1), FMath::FRandRange(0, 1))) * FMath::FRandRange(0.9, 1.1);
			}
		}
		
	}
}
