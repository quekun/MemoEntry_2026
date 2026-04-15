// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Bullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "InitBullet.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API AInitBullet : public ABullet
{
	GENERATED_BODY()
public:
	AInitBullet();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;
};
