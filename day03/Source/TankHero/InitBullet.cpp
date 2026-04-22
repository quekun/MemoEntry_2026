// Fill out your copyright notice in the Description page of Project Settings.


#include "InitBullet.h"
#include "Components/SceneComponent.h"  

AInitBullet::AInitBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BulletMesh;
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	Damage = 25.f;
}

void AInitBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AInitBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

