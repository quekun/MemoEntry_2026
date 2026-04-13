// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBall.h"
#include "WeaponBall.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API AWeaponBall : public APickUpBall
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWeaponBall();

	virtual void GetEffect() override;
};
