// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"

class UNiagaraSystem;

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
	virtual void BeginPlay() override;

private:
	// 内部执行函数，不再需要外部传入参数，直接用父类的 BounceFrequency
	void ExecuteLaserBounce();

	// 控制Tick只执行一次的开关
	bool bHasFiredLaser = false;


public:
	virtual void Tick(float DeltaTime) override;

protected:
	// 激光最大射程
	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	float LaserRange = 10000.f;

	// Niagara 激光光束特效
	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	UNiagaraSystem* LaserBeamEffect;
};
