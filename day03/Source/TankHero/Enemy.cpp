// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    TrackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrackMesh"));
    Barrel_LMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel_LMesh"));
    Barrel_RMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel_RMesh"));
    HullMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HullMesh"));
    ArmorSkirtMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmorSkirtMesh"));

    TrackMesh->SetupAttachment(RootComponent);

    HullMesh->SetupAttachment(RootComponent);

    ArmorSkirtMesh->SetupAttachment(RootComponent);

    ChassisMesh->SetupAttachment(HullMesh);

    Barrel_LMesh->SetupAttachment(ChassisMesh);

    Barrel_RMesh->SetupAttachment(ChassisMesh);

    HatchMesh->SetupAttachment(ChassisMesh);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    //GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AEnemy::CheckFireCondition, FireRate, true);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AEnemy::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void AEnemy::Fire()
{
    //²¹³äµÐÈËÂß¼­

    bIsFiringCoolDown = true;
}



