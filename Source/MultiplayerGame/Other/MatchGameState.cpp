// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchGameState.h"
#include <MultiplayerGame/Weapons/DefaultWeapon.h>
#include <MultiplayerGame/Bullets/DefaultBullet.h>
#include <MultiplayerGame/Other/DefaultPlayerState.h>
#include <Net/UnrealNetwork.h>
#include "DefaultPlayerController.h"
#include <MultiplayerGame/Widgets/MatchInfo.h>
#include <MultiplayerGame/Widgets/WarmUpWidget.h>
#include <MultiplayerGame/Widgets/PauseMenuWidget.h>
#include "Kismet/GameplayStatics.h"




void AMatchGameState::OnRep_MatchInProgress()
{
	ADefaultPlayerController* PC;
	for (int i = 0; i < PlayerArray.Num(); i++) {
		PC = Cast<ADefaultPlayerController>(PlayerArray[i]->GetOwner());
		if (PC != nullptr) {
			if (MatchInProgress) {
				PC->WarmUp->SetVisibility(ESlateVisibility::Hidden);
			}
			else {
				PC->WarmUp->SetVisibility(ESlateVisibility::Visible);
				PC->MatchStats->SetVisibility(ESlateVisibility::Hidden);
			}
			return;
		}
	}
}

//void AMatchGameState::ChangeAllowedWeapons()
//{
//}
//
//void AMatchGameState::ChangeRestartTime_Implementation(float NewTime)
//{
//}
//
//void AMatchGameState::ChangeAllowedBullets()
//{
//}
//
//void AMatchGameState::ChangeisEndByTimer_Implementation(bool newBool)
//{
//}
//
//void AMatchGameState::ChangeisFrendlyFire_Implementation(bool newBool)
//{
//}
//
//void AMatchGameState::ChangeTeamsEqualPlayers_Implementation(bool newBool)
//{
//}
//
//void AMatchGameState::ChangeCountTeams_Implementation(int32 newInt)
//{
//}

void AMatchGameState::OnRep_Teams()
{
	ADefaultPlayerController* PC = Cast<ADefaultPlayerController>(UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0));
	PC->WarmUp->UpdateTeams();
}

void AMatchGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMatchGameState, AllowedWeapons);
	DOREPLIFETIME(AMatchGameState, AllowedBullets);
	DOREPLIFETIME(AMatchGameState, isEndByTimer);
	DOREPLIFETIME(AMatchGameState, isFrendlyFire);
	DOREPLIFETIME(AMatchGameState, TeamsEqualPlayers);
	DOREPLIFETIME(AMatchGameState, CountTeams);
	DOREPLIFETIME(AMatchGameState, Teams);
	DOREPLIFETIME(AMatchGameState, MaxKills);
	DOREPLIFETIME(AMatchGameState, MatchInProgress);
	DOREPLIFETIME(AMatchGameState, Time);
	DOREPLIFETIME(AMatchGameState, RestartTime);
	DOREPLIFETIME(AMatchGameState, Distance1);
	DOREPLIFETIME(AMatchGameState, Distance2);
	DOREPLIFETIME(AMatchGameState, Distance3);
	DOREPLIFETIME(AMatchGameState, DistanceKoefForBullet);
	DOREPLIFETIME(AMatchGameState, HealthKoef);
	DOREPLIFETIME(AMatchGameState, DistanceKoefForWeapon);
	DOREPLIFETIME(AMatchGameState, BulletKoef);
	DOREPLIFETIME(AMatchGameState, TargetDistance);
}
