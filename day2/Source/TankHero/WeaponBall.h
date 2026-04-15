// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBall.h"

class ABullet;
class ATank;
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

	UPROPERTY(EditAnywhere, Category = "Bullet")
	TSubclassOf<ABullet> BulletClass;//在编辑器中手动指定

	// 统一接口！参数只有 ATank*
	virtual void GetEffect(ATank* Tank) override;

};
