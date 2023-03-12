// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimManagerComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERGAME_API UAimManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAimManagerComponent();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AimComponent")
	FTransform RightArmTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AimComponent")
	FTransform LeftArmTransform;*/
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AimComponent")
	FTransform WeaponTransform;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AimComponent")
	float XOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AimComponent")
	float YOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AimComponent")
	float ZOffset;

protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
