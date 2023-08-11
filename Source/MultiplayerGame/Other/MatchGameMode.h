#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"


class AMatchGameState;
class ADefaultTeam;
class ASpectatorPawn;
class ADefaultPlayerController;
class ADefaultPlayerState;
class AAIController;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<APawn> AICharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AAIController> AIControllerClass;

	UFUNCTION(BlueprintCallable)
	void ChangeTeam(APlayerState* PS, int32 TeamIndex);

	UFUNCTION(BlueprintCallable)
	void AddBotToTeam(ADefaultTeam* Team);

	UFUNCTION(BlueprintCallable)
	void RemoveBotFromTeam(ADefaultTeam* Team);

	UFUNCTION(BlueprintCallable)
	void ChangeTeamByTeam(APlayerState* PS, ADefaultTeam* Team);

	int32 FindBetterTeam(APlayerState* PS);

	bool CanDamage(APlayerState* DamageReciver, APlayerState* DamageCauser);

	void ApplyDamageToCh(ACharacter* Ch, ACharacter* Ins, float Damage);

	bool CanChangeState(APlayerState* PS);

	void RedistributeByTeam();
	UFUNCTION()
	void OnRestart(AController* C);

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
