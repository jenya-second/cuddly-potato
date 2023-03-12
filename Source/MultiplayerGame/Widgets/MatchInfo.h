// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MatchInfo.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UMatchInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=MatchInfo)
	void RefreshUI();
};
