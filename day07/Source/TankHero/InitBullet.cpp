// Fill out your copyright notice in the Description page of Project Settings.


#include "InitBullet.h"
#include "Components/SceneComponent.h"  

AInitBullet::AInitBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	Damage = 25.f;
}

void AInitBullet::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.AddUnique(FName("Init"));
}

void AInitBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

