// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultBullet.h"
#include "ChaseBullet.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AChaseBullet : public ADefaultBullet
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Angle;
	
};
