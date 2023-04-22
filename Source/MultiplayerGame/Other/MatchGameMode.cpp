#include "MatchGameMode.h"
#include <MultiplayerGame/Other/MatchGameState.h>
#include <MultiplayerGame/Other/DefaultPlayerState.h>
#include <MultiplayerGame/MyActors/DefaultTeam.h>
#include <MultiplayerGame/Other/DefaultCharacter.h>
#include "GameFramework/SpectatorPawn.h"
#include "DefaultPlayerController.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>
#include <MultiplayerGame/MyActors/DispenserCreator.h>

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	RedistributeByTeam();
	
}

void AMatchGameMode::StartGame()
{ 
	if (GS() != nullptr) {
		GS()->MatchInProgress = true;
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADispenserCreator::StaticClass(), FoundActors);
		for (int i = 0; i < FoundActors.Num(); i++) {
			ADispenserCreator* DC = Cast<ADispenserCreator>(FoundActors[i]);
			if (DC != nullptr) {
				DC->StartCreating();
			}
		}
		for (int i = 0; i < GS()->PlayerArray.Num(); i++) {
			Cast<ADefaultPlayerState>(GS()->PlayerArray[i])->CleanStats();
			RestartPlayer(Cast<AController>(GS()->PlayerArray[i]->GetOwner()));		
		}
		for (int i = 0; i < GS()->Teams.Num(); i++) {
			GS()->Teams[i]->CleanStats();
		}
		if (GS()->isEndByTimer) {
			GetWorldTimerManager().SetTimer(ToEnd, this, &AMatchGameMode::EndGame, GS()->Time*60, false);
		}
	}
}

void AMatchGameMode::EndGame()
{
	if (GS() != nullptr) {
		GS()->MatchInProgress = false;
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADispenserCreator::StaticClass(), FoundActors);
		for (int i = 0; i < FoundActors.Num(); i++) {
			ADispenserCreator* DC = Cast<ADispenserCreator>(FoundActors[i]);
			if (DC != nullptr) {
				DC->StopCreating();
			}
		}
		for (int i = 0; i < GS()->PlayerArray.Num(); i++) {
			GetWorldTimerManager().ClearTimer(Cast<ADefaultPlayerState>(GS()->PlayerArray[i])->ForRespawn);
			AController* PC = Cast<AController>(GS()->PlayerArray[i]->GetOwner());
			PC->GetPawn()->Destroy();
			ADefaultPlayerController* DPC = Cast<ADefaultPlayerController>(PC);
			if (DPC) {
				DPC->OnEndGame();
			}
		}
	}
}

void AMatchGameMode::OnRestart(AController* C)
{
	if (C != nullptr) {
		RestartPlayer(C);
		ADefaultPlayerController* DPC = Cast<ADefaultPlayerController>(C);
		if (DPC != nullptr) {
			DPC->OnRestart();
		}
		
	}
}

void AMatchGameMode::SetIsStartAsSpectator(bool NewVar)
{
	bStartPlayersAsSpectators = NewVar;
}

bool AMatchGameMode::IsReadyToStartGame()
{
	if (GS() != nullptr) {
		if (GS()->MatchInProgress == true) {
			return false;
		}
		for (int i = 0; i < GS()->PlayerArray.Num(); i++) {
			if (!Cast<ADefaultPlayerState>(GS()->PlayerArray[i])->isReady) {
				return false;
			}
		}
		StartGame();
		return true;
	}
	return false;
}

AMatchGameState* AMatchGameMode::GS()
{
	return Cast<AMatchGameState>(GameState);
}

void AMatchGameMode::ChangeTeam(APlayerState* PS, int32 TeamIndex)
{
	ADefaultPlayerState* DPS = Cast<ADefaultPlayerState>(PS);
	if (TeamIndex == -1 || DPS == nullptr) {
		return;
	}
	ChangeTeamByTeam(PS, GS()->Teams[TeamIndex]);
}

void AMatchGameMode::AddBotToTeam(ADefaultTeam* Team)
{
	AAIController* AIC = Cast<AAIController>(GetWorld()->SpawnActor(AIControllerClass));
	if (AIC == nullptr) {
		return;
	}
	const FTransform tr;
	FActorSpawnParameters par = FActorSpawnParameters();
	par.Owner = AIC;
	ADefaultPlayerState* PS = Cast<ADefaultPlayerState>(GetWorld()->SpawnActor(PlayerStateClass, &tr, par));
	if (PS != nullptr) {
		AIC->PlayerState = PS;
		ChangeTeamByTeam(PS, Team);
		PS->isReady = true;
		PS->SetPlayerName(FString("Bot"));
	}
	
}

void AMatchGameMode::RemoveBotFromTeam(ADefaultTeam* Team)
{
	for (int i = 0; i < Team->TeamArray.Num(); i++) {
		AAIController* AIC = Cast<AAIController>(Team->TeamArray[i]->GetOwner());
		if (AIC != nullptr) {
			AIC->Destroy();
			
		}
	}
}

void AMatchGameMode::ChangeTeamByTeam(APlayerState* PS, ADefaultTeam* Team)
{
	ADefaultPlayerState* DPS = Cast<ADefaultPlayerState>(PS);
	if (DPS == nullptr) {
		return;
	}
	else {
		if (DPS->Team != nullptr) {
			DPS->Team->TeamArray.Remove(DPS);
		}
		Team->TeamArray.Add(DPS);
		DPS->Team = Team;
	}
}

int32 AMatchGameMode::FindBetterTeam(APlayerState* PS)
{
	if (GS() != nullptr) {
		if (GS()->TeamsEqualPlayers) {
			ADefaultTeam* NewTeam=GetWorld()->SpawnActor<ADefaultTeam>();
			return GS()->Teams.Add(NewTeam);
		}
		else {
			int32 ret=0;
			TArray<ADefaultTeam*> Teams = GS()->Teams;
			for (int i = 0; i < Teams.Num(); i++) {
				if (Teams[i]->TeamArray.Num() < Teams[ret]->TeamArray.Num()) {
					ret = i;
				}
			}
			return ret;
		}
	}
	return -1;
}

bool AMatchGameMode::CanDamage(APlayerState* DamageReciver, APlayerState* DamageCauser)
{
	ADefaultPlayerState* DR = Cast<ADefaultPlayerState>(DamageReciver);
	ADefaultPlayerState* DC = Cast<ADefaultPlayerState>(DamageCauser);
	if (DR != nullptr && DC != nullptr) {
		if ((DC->Team != DR->Team || GS()->isFrendlyFire) && DR->isDamageble) {
			return true;
		}
	}
	return false;
}

void AMatchGameMode::ApplyDamageToCh(ACharacter* Ch, ACharacter* Ins, float Damage)
{
	ADefaultCharacter* DCh = Cast<ADefaultCharacter>(Ch);
	ADefaultCharacter* ICh = Cast<ADefaultCharacter>(Ins);
	if (DCh != nullptr && ICh!=nullptr) {
		DCh->OnReceiveDamage(ICh);
		float NewShield = DCh->Shield - Damage;
		if (NewShield < 0) {
			float NewHelth = DCh->CurrentHealth + NewShield;
			if (NewHelth <= 0) {
				NewHelth = 0;
				DCh->Shield = 0;
				DCh->CurrentHealth = 0;
				OnDead(Ch, Ins);
			}
			DCh->CurrentHealth = NewHelth;
		}
		if (NewShield < 0) {
			NewShield = 0;
		}
		DCh->Shield = NewShield;
		ADefaultPlayerState* A = Cast<ADefaultPlayerState>(ICh->GetPlayerState());
		if (A != nullptr) {
			A->givenDamage += Damage;
		}
		A = Cast<ADefaultPlayerState>(DCh->GetPlayerState());
		if (A != nullptr) {
			A->recivedDamage += Damage;
		}
	}
}

bool AMatchGameMode::CanChangeState(APlayerState* PS)
{
	return !GS()->MatchInProgress && Cast<ADefaultPlayerState>(PS)->isAdmin;
}

void AMatchGameMode::RedistributeByTeam()
{
	for (int i = 0; i < GS()->Teams.Num(); i++) {
		GS()->Teams[i]->Destroy();
		/*GS()->Teams.Pop()->Destroy();*/
	}
	GS()->Teams.Empty();
	if (!GS()->TeamsEqualPlayers) {
		for (int i = 0; i < GS()->CountTeams; i++) {
			GS()->Teams.Add(GetWorld()->SpawnActor<ADefaultTeam>());
		}
	}
	for (int i = 0; i < GS()->PlayerArray.Num(); i++) {
		ChangeTeam(GS()->PlayerArray[i], FindBetterTeam(GS()->PlayerArray[i]));
	}
}

bool AMatchGameMode::IsOverKills()
{
	int32 a = 0;
	if (GS() != nullptr) {
		for (int i = 0; i < GS()->Teams.Num(); i++) {
			if (a < GS()->Teams[i]->Kills) {
				a = GS()->Teams[i]->Kills;
			}
		}
		return a >= GS()->MaxKills;
	}
	return false;
}

void AMatchGameMode::OnDead(ACharacter* Ch, ACharacter* Ins)
{
	ADefaultCharacter* DCh = Cast<ADefaultCharacter>(Ch);
	ADefaultCharacter* ICh = Cast<ADefaultCharacter>(Ins);
	if (DCh != nullptr && ICh != nullptr) {
		ADefaultPlayerState* A = Cast<ADefaultPlayerState>(ICh->GetPlayerState());
		ADefaultPlayerState* B = Cast<ADefaultPlayerState>(DCh->GetPlayerState());
		if (A != nullptr && B != nullptr) {
			A->kills++; 
			A->Team->Kills++;
			B->deaths++;
			B->Team->Deaths++;
			B->isDamageble = false;
			B->isDead = true;
			DCh->OnDead();
			DCh->DestroyWeapons();
			FTimerDelegate del;
			AController* C = Cast<AController>(DCh->GetOwner());
			if (C != nullptr) {
				ADefaultPlayerController* DPC = Cast<ADefaultPlayerController>(C);
				if (DPC != nullptr) {
					DPC->OnDead();
				}
				del.BindUFunction(this, FName("OnRestart"), C);
			}
			GetWorldTimerManager().SetTimer(B->ForRespawn,del,GS()->RestartTime, false);
		}
	}
	if (!GS()->isEndByTimer) {
		if (IsOverKills()) {
			EndGame();
		}
	}
}

void AMatchGameMode::Logout(AController* Controller)
{
	ADefaultPlayerState* DPS = Cast<ADefaultPlayerState>(Controller->PlayerState);
	if (GS()->TeamsEqualPlayers) {
		GS()->Teams.Remove(DPS->Team);
	}
	else {
		DPS->Team->TeamArray.Remove(DPS);
	}
	int32 A;
	bool B = false;
	if (DPS->isAdmin) {
		B = true;
	}
	Super::Logout(Controller);
	if (GS()->PlayerArray.Num() == 0) {
		EndGame();
		return;
	}
	if (B) {
		A = FMath::RandRange(0, GS()->PlayerArray.Num()-1);
		Cast<ADefaultPlayerState>(GS()->PlayerArray[A])->isAdmin = true;
	}
	IsReadyToStartGame();
}

void AMatchGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);
	
	ChangeTeam(PlayerController->PlayerState, FindBetterTeam(PlayerController->PlayerState));
	if (GS()->PlayerArray.Num() == 1) {
		Cast<ADefaultPlayerState>(PlayerController->PlayerState)->isAdmin = true;
	}
}

void AMatchGameMode::RestartPlayer(AController* Controller)
{
	AActor* PlayerStart = FindPlayerStart(Controller);
	if (PlayerStart != nullptr) {
		APawn* NewPawn;
		if (Cast<AAIController>(Controller) != nullptr) {
			NewPawn = Cast<APawn>(GetWorld()->SpawnActor(AICharacterClass, &PlayerStart->GetTransform()));
		}
		else {
			NewPawn = Cast<APawn>(GetWorld()->SpawnActor(DefaultPawnClass, &PlayerStart->GetTransform()));
		}
		if (NewPawn != nullptr) {
			APawn* A = Controller->GetPawn();
			Controller->Possess(NewPawn);
			if (A != nullptr) {
				A->Destroy();
			}
		}
	}
}

bool AMatchGameMode::ShouldSpawnAtStartSpot(AController* Controller)
{
	return false;
}
