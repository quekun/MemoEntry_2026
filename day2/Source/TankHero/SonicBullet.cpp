// Fill out your copyright notice in the Description page of Project Settings.


#include "SonicBullet.h"

ASonicBullet::ASonicBullet()
{
    PrimaryActorTick.bCanEverTick = true;
	RootComponent = BulletMesh;

    ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

    Damage = 50.f;
}

void ASonicBullet::BeginPlay()
{
    Super::BeginPlay();
}


void ASonicBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    LifeSpan += DeltaTime;
    float SideMultiplier = FMath::Pow(1.5f, LifeSpan);
    FVector NewRelativeScale(1,1,1);
    NewRelativeScale.Y = SideMultiplier;
    BulletMesh->SetRelativeScale3D(NewRelativeScale);
}