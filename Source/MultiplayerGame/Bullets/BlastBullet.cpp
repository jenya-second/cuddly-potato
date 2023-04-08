#include "BlastBullet.h"

void ABlastBullet::NotifyActorBeginOverlap(AActor* Actor)
{
	ReceiveActorBeginOverlap(Actor);
	
	if (Actor == GetOwner()) {
		return;
	}
	if (GetWorld()->GetAuthGameMode()) {
		FCollisionQueryParams Params;
		
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		TArray<FHitResult> res;
		FCollisionObjectQueryParams Obj;
		Obj.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
		if (GetWorld()->SweepMultiByObjectType(res, GetActorLocation(), GetActorLocation()+FVector(0,0,1), FQuat(), Obj, FCollisionShape::MakeSphere(Radius), Params)) {
			for (int i = 0; i < res.Num(); i++) {
				/*FString x = GetDebugName(res[i].Actor.Get());
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, x);*/
				DoDamage(res[i].GetActor());
			}
		}
	}
	Destroy();
}

