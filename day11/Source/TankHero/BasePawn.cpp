// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Bullet.h"

#include "Tank.h"

#include "Components/WidgetComponent.h"
// 如果你需要强转为你自己的Widget类，记得包含它的头文件
#include "HUDWidget.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    
    ChassisMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChassisMesh"));
    
    HatchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HatchMesh"));
    
    wheelsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("heels_02_Mesh"));
    
    BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));

    HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComp"));
    
    HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));

    SetRootComponent(CapsuleComp);
    wheelsMesh->SetupAttachment(RootComponent);
    HealthWidgetComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
    Super::BeginPlay();
    if (HealthWidgetComp)
    {
        // 从组件中获取真正生成的 UI 实例，并转为你自己的 UHUDWidget 类
        HealthWidget = Cast<UHUDWidget>(HealthWidgetComp->GetUserWidgetObject());
    }
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
    if (this->ActorHasTag(FName("BounceUp")))
    {
        Bullet->BounceFrequency++;
    }
}

void ABasePawn::ResetFireCoolDown()
{
    bIsFiringCoolDown = false;
}

void ABasePawn::HandleDestruction()
{
    if (DeathParticles&& DeathSound)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetActorLocation(),
            GetActorRotation());

        UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
    }
}

void ABasePawn::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
    if (HealthWidget)
    {
        // 调用之前在 UHUDWidget 里写好的变色+更新进度条的函数
        HealthWidget->SetHealthBarPercent(CurrentHealth, MaxHealth);
    }
}





