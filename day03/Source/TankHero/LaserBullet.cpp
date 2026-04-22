// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBullet.h"

ALaserBullet::ALaserBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BulletMesh;

	Damage = 50.f;
}

void ALaserBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ALaserBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
