#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

class UUserWidget;
class UWarmUpWidget;
class UMatchInfo;
class UPauseMenuWidget;
/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller")
	TSubclassOf<UMatchInfo> MatchStatsClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller")
	TSubclassOf<UPauseMenuWidget> PauseMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller")
	TSubclassOf<UWarmUpWidget> WarmUpClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller")
	TSubclassOf<UUserWidget> CharacterWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	UMatchInfo* MatchStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	UPauseMenuWidget* PauseMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	UWarmUpWidget* WarmUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	UUserWidget* CharacterWidget;

	UFUNCTION(Client, Reliable)
	void RefreshUI();
	UFUNCTION(Client, Reliable)
	void OnDead();
	UFUNCTION(Client, Reliable)
	void OnRestart();
	UFUNCTION(Client, Reliable)
	void OnEndGame();
	UFUNCTION(Client, Reliable)
	void SetModeGameOnly();
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void OnFocusMenu();
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void OnUnFocusMenu();
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void OnPos();
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void OnUnPos();
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeRestartTime(float NewTime);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeIsEndByTimer(bool newBool);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeIsFrendlyFire(bool newBool);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeTeamsEqualPlayers(bool newBool);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeCountTeams(int32 newInt);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeMaxKills(int32 newInt);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeTime(float NewTime);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeDistanceKoefForBullet(float NewKoef);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeHealthKoef(float NewKoef);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeDistanceKoefForWeapon(float NewKoef);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeBulletKoef(float NewKoef);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeTargetDistance(float NewDistance);


	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AddBotToTeam(ADefaultTeam* Team);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RemoveBotFromTeam(ADefaultTeam* Team);
};
