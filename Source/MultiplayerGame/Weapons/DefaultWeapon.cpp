// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultWeapon.h"

// Sets default values
ADefaultWeapon::ADefaultWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	WeaponBody = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	RootComponent = WeaponBody;
	WeaponBody->SetCollisionProfileName("OverlapAll");
	WeaponBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADefaultWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultWeapon::PressShoot()
{
	UE_LOG(LogTemp, Warning, TEXT("Shoot"));
}

void ADefaultWeapon::UnPressShoot()
{
	UE_LOG(LogTemp, Warning, TEXT("UnPressShoot"));
}

void ADefaultWeapon::PressAlternativeShoot()
{
	UE_LOG(LogTemp, Warning, TEXT("AlternativeShoot"));
}

void ADefaultWeapon::UnPressAlternativeShoot()
{
	UE_LOG(LogTemp, Warning, TEXT("UnPressAlternativeShoot"));
}
