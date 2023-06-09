// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <MultiplayerGame/Bullets/DefaultBullet.h>
#include "BulletManagerComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERGAME_API UBulletManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletManagerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullets")
	TSubclassOf<ADefaultBullet> CurrentBullet;

	int32 IndexBullet = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullets")
	TArray<int32> CountBullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullets")
	TArray<TSubclassOf<ADefaultBullet>> BulletsClasses;

	void SetCurrentBullet(int32 Index);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
