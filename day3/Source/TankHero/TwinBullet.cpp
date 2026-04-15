// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinBullet.h"

#include "Components/SceneComponent.h"  

ATwinBullet::ATwinBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BulletMesh;
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
}

void ATwinBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ATwinBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


