// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffBall.h"
#include "ShieldBall.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API AShieldBall : public ABuffBall
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AShieldBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetEffect() override;
};
