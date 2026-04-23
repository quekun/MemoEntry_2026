// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBullet.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ALaserBullet::ALaserBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	Damage = 50.f;

	// 射线瞬间计算完成，不需要每帧Tick，建议关掉节省性能
	

	// 【重要】设置一个寿命，比如 1 秒。
	// 因为它是不移动的射线管理器，计算完后留着没用，等特效播完自动销毁，防止内存泄漏。
	InitialLifeSpan = 1.0f;
}

void ALaserBullet::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.AddUnique(FName("Laser"));
	// 【关键1】：完全禁用物理与碰撞！
	// 这样父类 ABullet 的 OnHit 就绝对不会被触发了，完美绕过基类逻辑。
	if (BulletMesh)
	{
		BulletMesh->SetVisibility(false);
		BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void ALaserBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("1111111111111111"));
	// 【关键2】：在生成后的第一帧执行激光射线
	// 此时 Pawn 的 Fire() 函数已经执行完毕，Owner 和 BounceFrequency 都已经是最新的了！
	if (!bHasFiredLaser)
	{
		
		ExecuteLaserBounce();
		bHasFiredLaser = true;

		// 射线瞬间计算完毕，以后再也不需要 Tick 了，彻底关闭以节省性能
		SetActorTickEnabled(false);
	}
}

void ALaserBullet::ExecuteLaserBounce()
{
	UWorld* World = GetWorld();
	if (!World) return;

	FVector CurrentStart = GetActorLocation();
	FVector CurrentDirection = GetActorForwardVector();

	// 直接使用基类继承来的 BounceFrequency ！
	for (int32 i = 0; i <= BounceFrequency; ++i)
	{
		FVector CurrentEnd = CurrentStart + (CurrentDirection * LaserRange);
		FHitResult Hit;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		// 使用基类继承来的 GetOwner() 忽略发射者（坦克）
		if (GetOwner())
		{
			QueryParams.AddIgnoredActor(GetOwner());
		}

		bool bHit = World->LineTraceSingleByChannel(Hit, CurrentStart, CurrentEnd, ECC_Visibility, QueryParams);
		FVector BeamEnd = bHit ? Hit.ImpactPoint : CurrentEnd;

		// 生成特效
		if (LaserBeamEffect)
		{
			UNiagaraComponent* BeamComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, LaserBeamEffect, CurrentStart);
			if (BeamComp)
			{
				BeamComp->SetVectorParameter(FName("BeamStart"), CurrentStart);
				BeamComp->SetVectorParameter(FName("BeamEnd"), BeamEnd);
			}
		}

		if (bHit)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				// 直接使用基类的 Damage
				UGameplayStatics::ApplyDamage(HitActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
			}

			// 计算反射角并推开一点点防止死循环
			CurrentDirection = FMath::GetReflectionVector(CurrentDirection, Hit.ImpactNormal);
			CurrentDirection.Normalize();
			CurrentStart = Hit.ImpactPoint + (Hit.ImpactNormal * 1.0f);
		}
		else
		{
			break;
		}
	}
}