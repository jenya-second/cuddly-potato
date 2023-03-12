// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"

class AMatchGameState;
class ADefaultTeam;
class ASpectatorPawn;
class ADefaultPlayerController;
class ADefaultPlayerState;
/*
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetIsStartAsSpectator(bool NewVar);

	bool IsReadyToStartGame();

	void ChangeTeam(APlayerState* PS, int32 TeamIndex);

	int32 FindBetterTeam(APlayerState* PS);

	bool CanDamage(APlayerState* DamageReciver, APlayerState* DamageCauser);

	void ApplyDamageToCh(ACharacter* Ch, ACharacter* Ins, float Damage);

	bool CanChangeState(APlayerState* PS);

	void RedistributeByTeam();
	UFUNCTION()
	void OnRestart(ADefaultPlayerController* PC);

	virtual void BeginPlay() override;

	virtual void Logout(AController* Controller) override;

	virtual void PostLogin(APlayerController* PlayerController) override;

	virtual void RestartPlayer(AController* Controller) override;

	virtual bool ShouldSpawnAtStartSpot(AController* Controller) override;
protected:
	bool IsOverKills();

	void OnDead(ACharacter* Ch, ACharacter* Ins);

	void StartGame();

	void EndGame();

	AMatchGameState* GS();

	FTimerHandle ToEnd;
};
