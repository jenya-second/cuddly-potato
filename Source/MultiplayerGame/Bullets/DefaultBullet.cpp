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
	BulletBody = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	RootComponent = BulletBody;
	BulletBody->SetGenerateOverlapEvents(true);
	BulletBody->SetCollisionProfileName("OverlapAll");
	BulletBody->SetEnableGravity(false);
	BulletBody->SetNotifyRigidBodyCollision(true);
	BulletBody->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletBody->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BulletBody->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	BulletBody->SetSimulatePhysics(true);
}

void ADefaultBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultBullet::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	AMatchGameMode* GM = Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode());
	if (GetLocalRole() == ROLE_Authority) {
		ADefaultCharacter* Ch = Cast<ADefaultCharacter>(Other);
		if (Ch != nullptr) {
			APlayerState* PS = Cast<ADefaultCharacter>(GetOwner())->GetPlayerState();
			if (GM->CanDamage(Ch->GetPlayerState(), PS)) {
				GM->ApplyDamageToCh(Ch, Cast<ACharacter>(GetOwner()), Damage);
			}
		}
		Destroy();
	}
}

void ADefaultBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}