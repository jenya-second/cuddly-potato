// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBullet.h"
#include <MultiplayerGame/Other/DefaultCharacter.h>

void AShieldBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AShieldBullet::DoDamage(AActor* Actor)
{
	Super::DoDamage(Actor);
	ADefaultCharacter* ACh = Cast<ADefaultCharacter>(Actor);
	ADefaultCharacter* Ch = Cast<ADefaultCharacter>(GetOwner());
	if (Ch != nullptr && ACh != nullptr) {
		if (Ch->Shield + ShieldIncrease > 100) {
			Ch->Shield = 100;
		}
		else {
			Ch->Shield += ShieldIncrease;
		}
	}
}
