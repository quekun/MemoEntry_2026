// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueLaserWall.h"

// Sets default values
ABlueLaserWall::ABlueLaserWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
}

// Called when the game starts or when spawned
void ABlueLaserWall::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.AddUnique(FName("BlueLaserWall"));
}

// Called every frame
void ABlueLaserWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

