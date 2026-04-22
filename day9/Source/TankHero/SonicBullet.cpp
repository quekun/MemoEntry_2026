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
    InitialScale = BulletMesh->GetRelativeScale3D();
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

    FVector NewRelativeScale = InitialScale;

    // 0.2 * 1.0 = 0.2 (第一帧不变)
    // 0.2 * 2.0 = 0.4 (正常放大)
    NewRelativeScale.Y = InitialScale.Y * SideMultiplier;

    BulletMesh->SetRelativeScale3D(NewRelativeScale);
}