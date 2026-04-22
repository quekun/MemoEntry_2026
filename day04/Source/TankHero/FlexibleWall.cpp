// Fill out your copyright notice in the Description page of Project Settings.


#include "FlexibleWall.h"
#include "Mover.h"
#include "Engine/OverlapResult.h"

// Sets default values
AFlexibleWall::AFlexibleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
    Mover = CreateDefaultSubobject<UMover>(TEXT("Mover"));
}


// Called when the game starts or when spawned
void AFlexibleWall::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.AddUnique(FName("FlexibleWall"));
}

// Called every frame
void AFlexibleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlexibleWall::AttemptToRaise()
{
    // 这样无论墙下沉到哪里，检测盒永远固定在地面上方的那个“门口”
    FVector CheckLocation = Mover->StartLocation + FVector(0, 0, 100.0f);

    // 稍微把盒子减薄一点，进一步降低碰到地板的概率
    FVector BoxHalfSize = FVector(80.f, 80.f, 40.f);

    //DrawDebugBox(GetWorld(), CheckLocation, BoxHalfSize, FColor::Green, false, 0.5f, 0, 2.0f);

    TArray<FOverlapResult> OutOverlaps;
    FCollisionObjectQueryParams ObjectQueryParams(FCollisionObjectQueryParams::InitType::AllObjects);
    ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

    // 【修正】初始化 QueryParams 并忽略墙体自己
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    bool bIsTankOnTop = GetWorld()->OverlapMultiByObjectType(
        OutOverlaps,
        CheckLocation,
        GetActorQuat(),
        ObjectQueryParams,
        FCollisionShape::MakeBox(BoxHalfSize),
        QueryParams
    );

    // 如果上面有坦克
    if (bIsTankOnTop)
    {
        for (auto& Overlap : OutOverlaps)
        {
            UE_LOG(LogTemp, Warning, TEXT("Blocked by: %s"), *Overlap.GetActor()->GetName());
        }

        // 坦克还在！延迟 0.5 秒再次尝试，直到坦克离开
        GetWorldTimerManager().SetTimer(RaiseTimerHandle, this, &AFlexibleWall::AttemptToRaise, 0.5f, false);
    }
    else
    {
        // 没坦克了，可以上升
        RaiseWall();
    }
}

void AFlexibleWall::RaiseWall()
{
    IsLower = false;

    /*WallMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    WallMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);*/

    Mover->SetShouldMove(IsLower);
}

void AFlexibleWall::LowerWall()
{
    IsLower = true;

    /*WallMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    WallMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);*/

    // 开启计时器，时间到后尝试上升
    GetWorldTimerManager().SetTimer(RaiseTimerHandle, this, &AFlexibleWall::AttemptToRaise, WallLowerDuration, false);

    Mover->SetShouldMove(IsLower);
}

