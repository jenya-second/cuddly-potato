// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DefaultBullet.generated.h"

UCLASS()
class MULTIPLAYERGAME_API ADefaultBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	UStaticMeshComponent* BulletBody;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	UProjectileMovementComponent* ProjectileComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;	
	virtual void NotifyActorBeginOverlap(AActor* Actor) override;
	virtual void DoDamage(AActor* Actor);

};
