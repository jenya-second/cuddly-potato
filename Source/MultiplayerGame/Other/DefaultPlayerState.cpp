// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include <MultiplayerGame/Other/MatchGameMode.h>

void ADefaultPlayerState::SwitchIsReady_Implementation(bool NewIsReady)
{
	isReady = NewIsReady;
	AMatchGameMode* GM = Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode());
	if (GM != nullptr) {
		if (Cast<AMatchGameState>(GM->GameState)->MatchInProgress) {
			GM->RestartPlayer(Cast<AController>(GetOwner()));
		}
		else {
			GM->IsReadyToStartGame();
		}
	}
}

void ADefaultPlayerState::CleanStats()
{
	isReady = false;
	kills = 0;
	deaths = 0;
	givenDamage = 0;
	recivedDamage = 0;
	isDamageble = true;
	isDead = false;
}

void ADefaultPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADefaultPlayerState, isReady);
	DOREPLIFETIME(ADefaultPlayerState, isDead);
	DOREPLIFETIME(ADefaultPlayerState, kills);
	DOREPLIFETIME(ADefaultPlayerState, deaths);
	DOREPLIFETIME(ADefaultPlayerState, givenDamage);
	DOREPLIFETIME(ADefaultPlayerState, recivedDamage);
	DOREPLIFETIME(ADefaultPlayerState, Team);
	DOREPLIFETIME(ADefaultPlayerState, isAdmin);
}
