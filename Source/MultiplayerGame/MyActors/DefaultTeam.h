// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultTeam.generated.h"

class ADefaultPlayerState;

UCLASS()
class MULTIPLAYERGAME_API ADefaultTeam : public AActor
{
	GENERATED_BODY()
	
public:	
	ADefaultTeam();

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Team")
	TArray<ADefaultPlayerState*> TeamArray;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Team")
	int32 Kills;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Team")
	int32 Deaths;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Team")
	FColor TeamColor;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void CleanStats();
};
