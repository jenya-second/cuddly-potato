// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseBullet.h"

void AChaseBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AChaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FCollisionQueryParams Params;
	Params.bFindInitialOverlaps = true;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	FHitResult res;
	FCollisionObjectQueryParams Obj;
	Obj.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	if (GetWorld()->SweepSingleByObjectType(res, GetActorLocation(), GetActorLocation(), FQuat(), Obj, FCollisionShape::MakeSphere(Radius), Params)) {
		FVector v1 = res.Actor->GetActorLocation() - FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z-50);
		FVector v2 = ProjectileComponent->Velocity;
		FVector XYZ = v2 ^ v1;
		
		ProjectileComponent->Velocity = v2.RotateAngleAxis(Angle*DeltaTime, XYZ.GetClampedToSize(-1, 1));

	}

}

