// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "DefaultGameSession.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API ADefaultGameSession : public AGameSession
{
	GENERATED_BODY()
public:
	virtual void RegisterServer() override;


};
