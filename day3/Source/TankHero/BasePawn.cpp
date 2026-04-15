// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "TwinBullet.h"

#include "Components/BoxComponent.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    
    ChassisMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChassisMesh"));
    
    HatchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HatchMesh"));
    
    wheelsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("heels_02_Mesh"));
    
    BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));

    SetRootComponent(BoxComp);
    wheelsMesh->SetupAttachment(RootComponent);
    
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::Fire()
{
    if (bIsFiringCoolDown)
    {
        return;
    }
    FVector SpawnLocation = BulletSpawnPoint->GetComponentLocation();
    FRotator SpawnRotation = BulletSpawnPoint->GetComponentRotation();
    ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation);
    if (Bullet)
    {
        Bullet->SetOwner(this);
    }
    //冷却为真放在子类
    GetWorldTimerManager().SetTimer(
        FireTimerHandle,	// 计时器句柄
        this,				// 当前对象
        &ABasePawn::ResetFireCoolDown, // 冷却结束调用的函数
        FireRate,			// 间隔时间（秒）
        false				// 不循环
    );
}

void ABasePawn::ResetFireCoolDown()
{
    bIsFiringCoolDown = false;
}

void ABasePawn::HandleDestruction()
{
    if (DeathParticles)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetActorLocation(),
            GetActorRotation());

        UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
    }
}



