// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "InputAction.h"

#include "PickUpBall.h"

#include "Components/StaticMeshComponent.h"

#include "Components/BoxComponent.h"

#include "EnhancedInputComponent.h"

#include "Kismet/GameplayStatics.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

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
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    if (TurretMesh)
    {
        MeshInternalOrigin = TurretMesh->GetRelativeLocation();
    }
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
    BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ATank::GetBall);
    SetPlayerEnabled(false);
}

void ATank::GetBall(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    APickUpBall* PickUpBall = Cast<APickUpBall>(OtherActor);
    if (!PickUpBall) return;

    // 让球执行效果（把子弹蓝图传给坦克）
    PickUpBall->GetEffect(this);
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
    SetPlayerEnabled(false);
    IsAlive = false;
}

void ATank::SetPlayerEnabled(bool Enabled)
{
    if (PlayerController)
    {
        if (Enabled)
        {
            EnableInput(PlayerController);
        }
        else
        {
            DisableInput(PlayerController);
        }
        PlayerController->bShowMouseCursor = Enabled;
    }
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

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
}

void ATank::MoveInput(const FInputActionValue& Value)
{
    float InputValue = Value.Get<float>();

    FVector DeltaLocal(0, 0, 0);

    DeltaLocal.Y = Speed * InputValue * GetWorld()->GetDeltaSeconds();

    FVector TargetLocation = FVector(0.f, InputValue * MoveShake, 0.f);

    FVector CurrentLocation = ChassisMesh->GetRelativeLocation();

    ChassisMesh->SetRelativeLocation(FMath::VInterpTo(CurrentLocation, TargetLocation,

        GetWorld()->GetDeltaSeconds(), MoveShake));

    AddActorLocalOffset(DeltaLocal, true);
}

void ATank::Fire()
{
    Super::Fire();
    if (!bIsFiringCoolDown)
    {
        CurrentRecoilOffset = FVector(0.f, -RecoilStrength, 0.f);
        if (TurretMesh)
        {
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

    FRotator TargetRotation = FRotator(0.f, InputValue * TurnShake, 0.f);

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
    }
}







