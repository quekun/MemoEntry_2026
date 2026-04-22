// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "SonicBullet.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API ASonicBullet : public ABullet
{
	GENERATED_BODY()
public:
	ASonicBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float ExpandSpeed = 2.f;

	UPROPERTY(VisibleAnywhere)
	float LifeSpan=0;

	UPROPERTY(EditAnywhere)
	float MaxLifeSpan = 2.0f;


	FVector InitialScale;
};
