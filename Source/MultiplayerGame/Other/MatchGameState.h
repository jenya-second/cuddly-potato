// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MatchGameState.generated.h"

class ADefaultWeapon;
class ADefaultBullet;
class ADefaultPlayerState;
class ADefaultTeam;

/*
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AMatchGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	TArray<TSubclassOf<ADefaultWeapon>> AllowedWeapons;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	TArray<TSubclassOf<ADefaultBullet>> AllowedBullets;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	bool isEndByTimer;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	bool isFrendlyFire;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	bool TeamsEqualPlayers;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	float RestartTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	int32 CountTeams;
	UPROPERTY(ReplicatedUsing=OnRep_Teams, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	TArray <ADefaultTeam*> Teams;
	UPROPERTY(ReplicatedUsing = OnRep_MatchInProgress, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	bool MatchInProgress = false;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	int32 MaxKills=1;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "GameStateSettings")
	float Time;

	UFUNCTION()
	void OnRep_MatchInProgress();
	/*UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeRestartTime(float NewTime);
	UFUNCTION()
	void ChangeAllowedWeapons();
	UFUNCTION()
	void ChangeAllowedBullets();
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeisEndByTimer(bool newBool);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeisFrendlyFire(bool newBool);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeTeamsEqualPlayers(bool newBool);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeCountTeams(int32 newInt);*/
	UFUNCTION()
	void OnRep_Teams();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
