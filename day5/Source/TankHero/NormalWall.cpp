// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalWall.h"

// Sets default values
ANormalWall::ANormalWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
}


// Called when the game starts or when spawned
void ANormalWall::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.AddUnique(FName("NormalWall"));
}

// Called every frame
void ANormalWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

