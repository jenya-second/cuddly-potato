// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultBullet.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>
#include <MultiplayerGame/Other/MatchGameMode.h>
#include <Components/StaticMeshComponent.h>

ADefaultBullet::ADefaultBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileComponent->SetIsReplicated(true);
	ProjectileComponent->bForceSubStepping = true;
	BulletBody = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	RootComponent = BulletBody;
	BulletBody->SetGenerateOverlapEvents(true);
	BulletBody->SetCollisionProfileName("OverlapAll");
	BulletBody->SetEnableGravity(false);
	BulletBody->SetNotifyRigidBodyCollision(true);
	BulletBody->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BulletBody->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BulletBody->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
}

void ADefaultBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultBullet::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	
}

void ADefaultBullet::NotifyActorBeginOverlap(AActor* Actor)
{
	Super::NotifyActorBeginOverlap(Actor);
	DoDamage(Actor);
	Destroy();
}

void ADefaultBullet::DoDamage(AActor* Actor)
{
	AMatchGameMode* GM = Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode());
	if (GetLocalRole() == ROLE_Authority) {
		ADefaultCharacter* Ch = Cast<ADefaultCharacter>(Actor);
		if (Ch != nullptr) {
			APlayerState* PS = Cast<ADefaultCharacter>(GetOwner())->GetPlayerState();
			if (GM->CanDamage(Ch->GetPlayerState(), PS)) {
				GM->ApplyDamageToCh(Ch, Cast<ACharacter>(GetOwner()), Damage);
			}
		}
	}
}

void ADefaultBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}