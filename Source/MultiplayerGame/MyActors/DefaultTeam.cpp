// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultTeam.h"
#include <Net/UnrealNetwork.h>

// Sets default values
ADefaultTeam::ADefaultTeam()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
	Kills = 0;
	Deaths = 0;
}

void ADefaultTeam::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalRole() == ROLE_Authority) {
		TeamColor = FColor(FMath::FRandRange(0,255), FMath::FRandRange(0, 255), FMath::FRandRange(0, 255));
	}
}

// Called every frame
void ADefaultTeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultTeam::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADefaultTeam, TeamArray);
	DOREPLIFETIME(ADefaultTeam, Kills);
	DOREPLIFETIME(ADefaultTeam, Deaths);
	DOREPLIFETIME(ADefaultTeam, TeamColor);
}

void ADefaultTeam::CleanStats()
{
	Kills = 0;
	Deaths = 0;
}
