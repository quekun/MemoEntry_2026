// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"



#include "LaserBullet.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API ALaserBullet : public ABullet
{
	GENERATED_BODY()
public:
	ALaserBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
