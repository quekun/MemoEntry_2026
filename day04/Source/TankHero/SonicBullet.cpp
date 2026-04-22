// Fill out your copyright notice in the Description page of Project Settings.


#include "SonicBullet.h"

ASonicBullet::ASonicBullet()
{
    PrimaryActorTick.bCanEverTick = true;
	RootComponent = BulletMesh;
    Damage = 50.f;
}

void ASonicBullet::BeginPlay()
{
    Super::BeginPlay();
    this->Tags.AddUnique(FName("Sonic"));
}


void ASonicBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    LifeSpan += DeltaTime;

    if (LifeSpan >= MaxLifeSpan)
    {
        Destroy();
        return; 
    }

    float SideMultiplier = FMath::Pow(ExpandSpeed, LifeSpan);
    FVector NewRelativeScale(1,1,1);
    NewRelativeScale.Y = SideMultiplier;
    BulletMesh->SetRelativeScale3D(NewRelativeScale);
}