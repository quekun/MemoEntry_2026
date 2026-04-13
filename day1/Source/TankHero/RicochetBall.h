// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffBall.h"
#include "RicochetBall.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API ARicochetBall : public ABuffBall
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ARicochetBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetEffect() override;
};
