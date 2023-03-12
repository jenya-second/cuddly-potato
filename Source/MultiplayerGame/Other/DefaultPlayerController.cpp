// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include <MultiplayerGame/Widgets/MatchInfo.h>
#include <MultiplayerGame/Widgets/WarmUpWidget.h>
#include <MultiplayerGame/Widgets/PauseMenuWidget.h>
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MatchGameState.h"
#include "MatchGameMode.h"

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalController()) {
		PauseMenu = CreateWidget<UPauseMenuWidget>(this, PauseMenuClass);
		MatchStats = CreateWidget<UMatchInfo>(this, MatchStatsClass);
		WarmUp = CreateWidget<UWarmUpWidget>(this, WarmUpClass);
		PauseMenu->AddToViewport(0);
		MatchStats->AddToViewport(0);
		WarmUp->AddToViewport(0);
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		MatchStats->SetVisibility(ESlateVisibility::Hidden);
		WarmUp->SetVisibility(ESlateVisibility::Visible);
		FInputModeUIOnly Mode;
		Mode.SetWidgetToFocus(WarmUp->GetCachedWidget());
		SetInputMode(Mode);
		bShowMouseCursor = true;
		
	}
}

void ADefaultPlayerController::OnFocusMenu_Implementation()
{
	/*FInputModeUIOnly Mode;*/
	FInputModeGameAndUI Mode;
	Mode.SetWidgetToFocus(PauseMenu->GetCachedWidget());
	PauseMenu->SetVisibility(ESlateVisibility::Visible);
	bShowMouseCursor = true;
	/*Mode.SetLockMouseToViewportBehavior(EMouseLockMode::)*/
	SetInputMode(Mode);
}

void ADefaultPlayerController::OnUnFocusMenu_Implementation()
{
	FInputModeGameOnly Mode;
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	SetInputMode(Mode);
	bShowMouseCursor = false;
}

void ADefaultPlayerController::SetModeGameOnly_Implementation()
{
	FInputModeGameOnly Mode;
	SetInputMode(Mode);
	bShowMouseCursor = false;
}

void ADefaultPlayerController::RefreshUI_Implementation()
{
	if (MatchStats != nullptr) {
		MatchStats->RefreshUI();
	}
}

void ADefaultPlayerController::OnEndGame_Implementation()
{
	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(WarmUp->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}

void ADefaultPlayerController::OnDead_Implementation()
{
	if (MatchStats != nullptr) {
		MatchStats->SetVisibility(ESlateVisibility::Visible);
	}
}

void ADefaultPlayerController::OnRestart_Implementation()
{
	if (MatchStats != nullptr) {
		MatchStats->SetVisibility(ESlateVisibility::Hidden);
	}
}


void ADefaultPlayerController::ChangeRestartTime_Implementation(float NewTime)
{
	if (Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->CanChangeState(PlayerState)) {
		Cast<AMatchGameState>(GetWorld()->GetGameState())->RestartTime = NewTime;
	}
}

void ADefaultPlayerController::ChangeIsEndByTimer_Implementation(bool newBool)
{
	if (Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->CanChangeState(PlayerState)) {
		Cast<AMatchGameState>(GetWorld()->GetGameState())->isEndByTimer = newBool;
	}
}

void ADefaultPlayerController::ChangeIsFrendlyFire_Implementation(bool newBool)
{
	if (Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->CanChangeState(PlayerState)) {
		Cast<AMatchGameState>(GetWorld()->GetGameState())->isFrendlyFire = newBool;
	}
}

void ADefaultPlayerController::ChangeTeamsEqualPlayers_Implementation(bool newBool)
{
	if (Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->CanChangeState(PlayerState)) {
		Cast<AMatchGameState>(GetWorld()->GetGameState())->TeamsEqualPlayers = newBool;
		Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->RedistributeByTeam();
	}
}

void ADefaultPlayerController::ChangeCountTeams_Implementation(int32 newInt)
{
	if (Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->CanChangeState(PlayerState)) {
		Cast<AMatchGameState>(GetWorld()->GetGameState())->CountTeams = newInt;
		Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->RedistributeByTeam();
	}
}

void ADefaultPlayerController::ChangeMaxKills_Implementation(int32 newInt)
{
	if (Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->CanChangeState(PlayerState)) {
		Cast<AMatchGameState>(GetWorld()->GetGameState())->MaxKills = newInt;
	}
}

void ADefaultPlayerController::ChangeTime_Implementation(float NewTime)
{
	if (Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode())->CanChangeState(PlayerState)) {
		Cast<AMatchGameState>(GetWorld()->GetGameState())->Time = NewTime;
	}
}
