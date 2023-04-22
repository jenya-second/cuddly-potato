#include "DispenserCreator.h"
#include <MultiplayerGame/Bullets/DefaultBullet.h>
#include <MultiplayerGame/MyActors/Dispenser.h>
#include <MultiplayerGame/Other/DefaultCharacter.h>

ADispenserCreator::ADispenserCreator()
{
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetGenerateOverlapEvents(false);
	DispenserCreatorBody = CreateDefaultSubobject<UStaticMeshComponent>("DispenserBody");
	DispenserCreatorBody->SetupAttachment(RootComponent);
	DispenserCreatorBody->SetCollisionProfileName("NoCollision");
}

void ADispenserCreator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADispenserCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADispenserCreator::StartCreating()
{
	GetWorldTimerManager().SetTimer(ResetHandle, this, &ADispenserCreator::CreateRandomDespenser, CreatingTime, true, CreatingTime);
}

void ADispenserCreator::StopCreating()
{
	GetWorldTimerManager().ClearTimer(ResetHandle);
}

void ADispenserCreator::CreateRandomDespenser()
{
	int32 a = FMath::RandHelper(BulletClasses.Num());
	CreateDespenser(BulletClasses[a]);
}

void ADispenserCreator::CreateDespenser(TSubclassOf<ADefaultBullet> BulletClass)
{
	const FTransform SpawnTransform = GetActorTransform();
	ADispenser* Actor = Cast<ADispenser>(GetWorld()->SpawnActorDeferred<ADispenser>(DispenserClass, GetActorTransform()));
	Actor->BulletClass = BulletClass;
	Actor->FinishSpawning(SpawnTransform);
}

