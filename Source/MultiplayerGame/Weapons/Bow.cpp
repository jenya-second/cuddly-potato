#include "Bow.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

ABow::ABow() {
	TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
}

void ABow::BeginPlay()
{
	Super::BeginPlay();
	FOnTimelineFloat progressFunction{};
	CanFire = false;
	progressFunction.BindDynamic(this, &ABow::EffectProgress);
	TimeLine->SetTimelineLength(1);
	TimeLine->AddInterpFloat(Curve, progressFunction);
}

void ABow::SetCanFireTrue()
{
	CanFire = true;
}

void ABow::PrepareToShoot()
{
	TimeLine->PlayFromStart();
	GetWorldTimerManager().SetTimer(SetCanFireHandle, this, &ABow::SetCanFireTrue, 1, false);
}

void ABow::EffectProgress(float Value)
{
	PullKoef = Value;
}

void ABow::BotShoot() 
{
	UnPressShoot();
	PressShoot();
}

void ABow::PressShoot()
{
	ADefaultCharacter* PlayerOwner = Cast<ADefaultCharacter>(GetOwner());
	if (PlayerOwner != nullptr) {
		if (PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet] >= 1)
		{
			GetWorldTimerManager().SetTimer(ResetHandle, this, &ABow::PrepareToShoot, FireSpeed, false);
		}
	}
}

void ABow::PressAlternativeShoot()
{
}

void ABow::UnPressShoot()
{
	ADefaultCharacter* PlayerOwner = Cast<ADefaultCharacter>(GetOwner());
	GetWorldTimerManager().ClearTimer(SetCanFireHandle);
	if (PlayerOwner != nullptr) {
		if (GetWorldTimerManager().IsTimerActive(ResetHandle) || PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet] == 0) {
			GetWorldTimerManager().ClearTimer(ResetHandle);
		}
		else {
			const FTransform SpawnTransform = WeaponBody->GetSocketTransform("For_bullet");
			MulticastSpawnArrow(SpawnTransform, PullKoef);
			PlayerOwner->BulletManager->CountBullets[PlayerOwner->BulletManager->IndexBullet]--;
		}
		CanFire = false;
	}
}

void ABow::UnPressAlternativeShoot()
{
}

void ABow::MulticastSpawnArrow_Implementation(FTransform SpawnTransform, float Koef)
{
	ADefaultCharacter* PlayerOwner = Cast<ADefaultCharacter>(GetOwner());
	if (PlayerOwner != nullptr) {
		ADefaultBullet* Actor = Cast<ADefaultBullet>(GetWorld()->SpawnActorDeferred<ADefaultBullet>(PlayerOwner->BulletManager->CurrentBullet, SpawnTransform, PlayerOwner));
		if (Actor != nullptr) {
			Actor->Damage *= BulletDamageScale * Koef;
			Actor->LinearDamping = LinearDamp;
			Actor->FinishSpawning(SpawnTransform);
			FVector vect = SpawnTransform.Rotator().Vector() *
				Actor->Speed * BulletSpeedScale * Koef;

			Actor->ProjectileComponent->Velocity = vect;
		}
	}
}

//void ABow::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	DOREPLIFETIME(ABow, PullKoef);
//}
