// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "InputAction.h"

#include "PickUpBall.h"

#include "Components/StaticMeshComponent.h"

#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"

#include "Kismet/GameplayStatics.h"

#include "ShieldComponent.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

#include "PauseWidget.h"

#include "TankHeroGameInstance.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    AntennaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AntennaMesh"));
    ExhaustMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExhaustMesh"));
    Track_LMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Track_LMesh"));
    Track_RMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Track_RMesh"));
    BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    

    ChassisMesh->SetupAttachment(RootComponent);

    CameraComp->SetupAttachment(RootComponent);
    Track_LMesh->SetupAttachment(RootComponent);
    Track_RMesh->SetupAttachment(RootComponent);
    SpringArm->SetupAttachment(RootComponent);
        
    SpringArm->TargetArmLength = CameraHeight;
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritRoll = false;
    SpringArm->bInheritYaw = false;

    CameraComp->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

    ExhaustMesh->SetupAttachment(ChassisMesh);
    TurretMesh->SetupAttachment(ChassisMesh);

    BulletSpawnPoint->SetupAttachment(BarrelMesh);
    BarrelMesh->SetupAttachment(TurretMesh);
    AntennaMesh->SetupAttachment(TurretMesh);
    HatchMesh->SetupAttachment(TurretMesh);

    ShieldComp = CreateDefaultSubobject<UShieldComponent>(TEXT("ShieldComp"));
    ShieldComp->SetupAttachment(RootComponent);
    ShieldComp->ShieldMesh->SetupAttachment(ShieldComp);
    ShieldComp->ShieldMesh->SetVisibility(false);


    SpringArm->SetAbsolute(true, true, true);

    // 2. 始终俯视：把角度固定为朝下看 (Pitch=-80到-90度左右)
    SpringArm->SetWorldRotation(FRotator(-80.f, 0.f, 0.f));

    // 3. 升入高空：把摇臂拉长，直到能看清全图 (根据你的地图大小调整)
    SpringArm->TargetArmLength = 800.f;

    // 4. 关闭碰撞测试：防止摇臂碰到墙壁时突然拉近镜头
    SpringArm->bDoCollisionTest = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = Cast<APlayerController>(Controller);
    if (PC)
    {
        

        // 2. 强制设为仅游戏模式（极其重要！）
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
    }


    if (TurretMesh)
    {
        MeshInternalOrigin = TurretMesh->GetRelativeLocation();
    }

    BaseChassisLoc = ChassisMesh->GetRelativeLocation();
    BaseChassisRot = ChassisMesh->GetRelativeRotation();

    PlayerController = Cast<APlayerController>(Controller);
    if (PlayerController)
    {
        if (ULocalPlayer* LocalPlay = PlayerController->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem
                = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlay))
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }
    CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ATank::GetBall);
    this->Tags.AddUnique(FName("Tank"));
}




void ATank::GetBall(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    APickUpBall* PickUpBall = Cast<APickUpBall>(OtherActor);
    if (!PickUpBall) return;

    // 让球执行效果（把子弹蓝图传给坦克）
    PickUpBall->GetEffect(this);
    Noitem=false;
}

void ATank::SetNewBullet(TSubclassOf<ABullet> NewBullet)
{
    BulletClass = NewBullet;
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    IsAlive = false;
}

void ATank::BoostSpeedStart()
{
    Speed *= 2;
    GetWorldTimerManager().SetTimer(
        BoostSpeedTimerHandle,
        this,
        &ATank::BoostSpeedEnd,
        BoostSpeedDuration,
        false
    );

    UE_LOG(LogTemp, Log, TEXT("BoostSpeed Started, will end in %f seconds"), BoostSpeedDuration);
}

void ATank::BoostSpeedEnd()
{
    Speed /= 2;
    GetWorldTimerManager().ClearTimer(BoostSpeedTimerHandle);
    UE_LOG(LogTemp, Log, TEXT("BoostSpeed Ended "));
}

void ATank::ShieldStart()
{
    OnOpenShield.Broadcast();
    Defense = 100.f;
    this->Tags.AddUnique(FName("Shield"));
    GetWorldTimerManager().SetTimer(
        ShieldTimerHandle,
        this,
        &ATank::ShieldEnd,
        ShieldDuration,
        false
    );

    UE_LOG(LogTemp, Log, TEXT("Shield Started, will end in %f seconds"), ShieldDuration);
}

void ATank::ShieldEnd()
{
    OnCloseShield.Broadcast();
    Defense = 0;
    this->Tags.Remove(FName("Shield"));
    GetWorldTimerManager().ClearTimer(ShieldTimerHandle);
    UE_LOG(LogTemp, Log, TEXT("Shield Ended "));
}

void ATank::BounceUpStart()
{
    this->Tags.AddUnique(FName("BounceUp"));
    GetWorldTimerManager().SetTimer(
        BounceTimerHandle,
        this,
        &ATank::BounceUpEnd,
        BounceUpDuration,
        false
    );

    UE_LOG(LogTemp, Log, TEXT("Bounce Started, will end in %f seconds"), BounceUpDuration);
}

void ATank::BounceUpEnd()
{
    this->Tags.Remove(FName("BounceUp"));
    // 2. 习惯性清理句柄（防止某些逻辑误判定时器是否激活）
    GetWorldTimerManager().ClearTimer(BounceTimerHandle);

    UE_LOG(LogTemp, Log, TEXT("Bounce Ended and Tag Removed"));
}

void ATank::PauseGame()
{

    // 如果已经配了类
    if (PauseWidgetClass)
    {
        // 1. 暂停游戏世界时间
        UGameplayStatics::SetGamePaused(GetWorld(), true);

        // 2. 创建并显示暂停UI
        UPauseWidget* PauseMenu = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
        if (PauseMenu)
        {
            PauseMenu->AddToViewport();
        }

        // 3. 呼出鼠标，把操作模式改成“只响应UI”，这样玩家才好点按钮
        APlayerController* PC = Cast<APlayerController>(GetController());
        if (PC)
        {
            PC->bShowMouseCursor = true;
            PC->SetInputMode(FInputModeUIOnly()); // 这样按键盘才不会控制坦克乱动
        }
    }
}



// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FHitResult HitResult;
    if (PlayerController)
    {
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

        RotateTurret(HitResult.ImpactPoint);
    }
    if (!CurrentRecoilOffset.IsNearlyZero())
    {
        CurrentRecoilOffset = FMath::VInterpTo(
            CurrentRecoilOffset,
            FVector::ZeroVector,
            DeltaTime,
            RecoilRestoreSpeed
        );

        // 应用更新后的位置
        if(TurretMesh)
        {
            TurretMesh->SetRelativeLocation(MeshInternalOrigin + CurrentRecoilOffset);
        }
    }


    FVector MapCenter = FVector(0.f, 0.f, 0.f);

    // 2. 获取坦克的当前位置
    FVector TankPos = GetActorLocation();

    // 3. 核心魔法：计算相机的目标位置
    // FMath::Lerp 的第三个参数 Alpha 是跟随程度 (0.0 到 1.0)
    // - 如果是 0.0，相机死死盯在地图中心不动。
    // - 如果是 1.0，相机和坦克 1:1 移动 (你现在的状态)。
    // - 设置为 0.2 到 0.3：坦克移动时，相机只稍微跟着移动一点点 (满足"一定范围内跟随")
    FVector NewCameraPos = FMath::Lerp(MapCenter, TankPos, 0.4f);

    // 保持相机在水平面移动，不需要在 Z 轴（上下）跟随坦克颠簸
    NewCameraPos.Z = MapCenter.Z;

    UTankHeroGameInstance* GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());

    // 4. 把计算好的位置赋予弹簧臂
    if (GameInst&&SpringArm&& GameInst->bIsCameraFollowOn)
    {
        SpringArm->SetWorldLocation(NewCameraPos);
    }
}

void ATank::MoveInput(const FInputActionValue& Value)
{
    float InputValue = Value.Get<float>();

    FVector DeltaLocal(0, 0, 0);

    DeltaLocal.X = Speed * InputValue * GetWorld()->GetDeltaSeconds();

    FVector TargetLocation = BaseChassisLoc + FVector(InputValue * MoveShake, 0.f, 0.f);


    FVector CurrentLocation = ChassisMesh->GetRelativeLocation();

    ChassisMesh->SetRelativeLocation(FMath::VInterpTo(CurrentLocation, TargetLocation,

        GetWorld()->GetDeltaSeconds(), MoveShake));

    AddActorLocalOffset(DeltaLocal, true);
}

void ATank::RotateTurret(FVector LookAtTarget)
{
    FVector VectorToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
    TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), FRotator(0, VectorToTarget.Rotation().Yaw-90, 0),
        GetWorld()->GetDeltaSeconds(), TurretRotateRate));
}

void ATank::SetCameraFollow(bool bFollow)
{
    if (SpringArm)
    {
        // 如果开启跟随，使用相对位置（跟着坦克动）
        // 如果关闭跟随，使用绝对位置（停留在当前世界的坐标，不随坦克移动）
        SpringArm->SetUsingAbsoluteLocation(!bFollow);
    }
}

void ATank::Fire()
{
    Super::Fire();
    if (!bIsFiringCoolDown)
    {
        // 1. 定义局部的后坐力方向（炮管的纯正后方）
        FVector LocalRecoil = FVector( 0.f,-RecoilStrength, 0.f);

        // 2. 核心魔法：根据炮塔当前的旋转角度，把这个局部方向转换成实际应该偏移的方向！
        if (TurretMesh)
        {
            CurrentRecoilOffset = TurretMesh->GetRelativeRotation().RotateVector(LocalRecoil);

            // 3. 应用带角度的偏移量
            TurretMesh->SetRelativeLocation(MeshInternalOrigin + CurrentRecoilOffset);
        }
    }
    bIsFiringCoolDown = true;
}


void ATank::TurnInput(const FInputActionValue& Value)
{
    float InputValue = Value.Get<float>();

    FRotator DeltaLocal(0, 0, 0);

    DeltaLocal.Yaw = TurnRate * InputValue * GetWorld()->GetDeltaSeconds();

    FRotator TargetRotation = BaseChassisRot + FRotator(0.f, InputValue * TurnShake, 0.f);

    FRotator CurrentRotation = ChassisMesh->GetRelativeRotation();

    ChassisMesh->SetRelativeRotation(FMath::RInterpTo(CurrentRotation, TargetRotation,

        GetWorld()->GetDeltaSeconds(), TurnShake));

    AddActorLocalRotation(DeltaLocal, true);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
        EIC->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::TurnInput);
        EIC->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::Fire);
        EIC->BindAction(PauseGameAction, ETriggerEvent::Triggered, this, &ATank::PauseGame);
    }
}







