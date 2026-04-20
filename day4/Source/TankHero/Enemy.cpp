// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    TrackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrackMesh"));
    Barrel_LMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel_LMesh"));
    Barrel_RMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel_RMesh"));
    HullMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HullMesh"));
    ArmorSkirtMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmorSkirtMesh"));

    TrackMesh->SetupAttachment(RootComponent);
    HullMesh->SetupAttachment(RootComponent);
    ArmorSkirtMesh->SetupAttachment(RootComponent);

    ChassisMesh->SetupAttachment(HullMesh);
    Barrel_LMesh->SetupAttachment(ChassisMesh);
    Barrel_RMesh->SetupAttachment(ChassisMesh);
    HatchMesh->SetupAttachment(ChassisMesh);

    BulletSpawnPoint->SetupAttachment(Barrel_LMesh);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    // 给敌人打上标签
    this->Tags.AddUnique(FName("Enemy"));

    // 如果后续需要开火逻辑，可以解开此定时器
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

void AEnemy::RotateHull(FVector LookAtTarget)
{
    // 待实现旋转逻辑
}

void AEnemy::Fire()
{
    // 补充敌人开火逻辑
    Super::Fire();
    bIsFiringCoolDown = true;
}
