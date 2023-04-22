#include "Dispenser.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

ADispenser::ADispenser()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetGenerateOverlapEvents(true);
	DispenserBody = CreateDefaultSubobject<UStaticMeshComponent>("DispenserBody");
	DispenserBody->SetupAttachment(RootComponent);
	DispenserBody->SetCollisionProfileName("NoCollision");
}

void ADispenser::BeginPlay()
{
	Super::BeginPlay();
}

void ADispenser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADispenser::NotifyActorBeginOverlap(AActor* Actor)
{
	ADefaultCharacter* DC = Cast<ADefaultCharacter>(Actor);
	if (DC != nullptr) {
		TArray<TSubclassOf<ADefaultBullet>> BC = DC->BulletManager->BulletsClasses;
		for (int i = 0; i < BC.Num(); i++) {
			if (BC[i]->IsChildOf(BulletClass)) {
				DC->BulletManager->CountBullets[i] += NumOfBullets;
				Destroy();
				return;
			}
		}
		
	}
}

