// Fill out your copyright notice in the Description page of Project Settings.


#include "RedLaserWall.h"

// Sets default values
ARedLaserWall::ARedLaserWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
}


// Called when the game starts or when spawned
void ARedLaserWall::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.AddUnique(FName("RedLaserWall"));
}

// Called every frame
void ARedLaserWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

