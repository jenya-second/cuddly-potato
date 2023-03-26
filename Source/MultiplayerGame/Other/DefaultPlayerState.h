// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <MultiplayerGame/Other/MatchGameState.h>
#include "DefaultPlayerState.generated.h"

class ADefaultTeam;


/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API ADefaultPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSettings")
	bool isReady=false;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSettings")
	int32 kills;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSettings")
	int32 deaths;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSettings")
	float givenDamage;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSettings")
	float recivedDamage;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSettings")
	ADefaultTeam* Team;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSettings")
	bool isAdmin;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSettings")
	bool isDead;
	bool isDamageble = true;

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void SwitchIsReady(bool newIsReady);

	void CleanStats();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeTeam(ADefaultTeam* NewTeam);

	FTimerHandle ForRespawn;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
