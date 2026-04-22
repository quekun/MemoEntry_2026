// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinBullet.h"

#include "Components/SceneComponent.h"  

ATwinBullet::ATwinBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	Damage = 50.f;
}

void ATwinBullet::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.AddUnique(FName("Twin"));
}

void ATwinBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


