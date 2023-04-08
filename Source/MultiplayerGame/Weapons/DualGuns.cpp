#include "DualGuns.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

void ADualGuns::SetCanFireTrue()
{
	CanFire = true;
}

void ADualGuns::PressShoot()
{
	ADefaultCharacter* PlayerOwner = Cast<ADefaultCharacter>(GetOwner());
	if (PlayerOwner != nullptr) {
		if (CanFire && PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet] >= 1)
		{
			const FTransform SpawnTransform = WeaponBody->GetSocketTransform("For_bullet");
			MulticastSpawnBullet(SpawnTransform);
			CanFire = false;
			PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet]--;
		}
		if (!GetWorldTimerManager().IsTimerActive(ResetHandle))
		{
			GetWorldTimerManager().SetTimer(ResetHandle, this, &ADualGuns::SetCanFireTrue, FireSpeed, false);
		}
	}
}

void ADualGuns::PressAlternativeShoot()
{
}

void ADualGuns::UnPressShoot()
{
}

void ADualGuns::UnPressAlternativeShoot()
{
}

void ADualGuns::MulticastSpawnBullet_Implementation(FTransform SpawnTransform)
{
	ADefaultCharacter* PlayerOwner = Cast<ADefaultCharacter>(GetOwner());
	if (PlayerOwner != nullptr) {
		ADefaultBullet* Actor = Cast<ADefaultBullet>(GetWorld()->SpawnActorDeferred<ADefaultBullet>(PlayerOwner->BulletManager->CurrentBullet, SpawnTransform, PlayerOwner));
		if (Actor != nullptr) {
			Actor->Damage *= BulletDamageScale;
			Actor->LinearDamping = LinearDamp;
			Actor->FinishSpawning(SpawnTransform);
			FVector vect = SpawnTransform.Rotator().Vector() *
				Actor->Speed * BulletSpeedScale;
			Actor->ProjectileComponent->Velocity = vect;
		}
	}
}
