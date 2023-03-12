// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WarmUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UWarmUpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnReady();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateTeams();
};
