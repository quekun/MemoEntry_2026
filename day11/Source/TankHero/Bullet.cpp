// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "FlexibleWall.h"
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp_New"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor)
	{
		return;
	}
	if (!BounceFrequency)
	{
		Destroy();
	}
	if (OtherActor->ActorHasTag(FName("Enemy"))|| OtherActor->ActorHasTag(FName("Tank")))
	{
		if (OtherActor->ActorHasTag(FName("Tank")))
		{
			ATank* Tank = Cast<ATank>(OtherActor);
			Tank->Flawless = false;
		}
		AActor* MyOwner = GetOwner();
		if (MyOwner && OtherActor != this)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(),
				this, UDamageType::StaticClass());

			if (HitParticles&& HitSound)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles,
					GetActorLocation(), GetActorRotation());

				UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
			}
			if (HitCameraShakeClass)
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				if (PlayerController)
				{
					PlayerController->ClientStartCameraShake(HitCameraShakeClass);
				}
			}
		}
		Destroy();
		return;
	}
	//后续就是墙壁，红墙不用考虑，与子弹不会接触
	else if (OtherActor->ActorHasTag(FName("NormalWall")))
	{
		if (!this->ActorHasTag(FName("Sonic")))//不是音波子弹就进行后续
		{
			--BounceFrequency;
		}
	}
	else if (OtherActor->ActorHasTag(FName("BlueLaserWall")))
	{
		if (!this->ActorHasTag(FName("Sonic")))//不是音波子弹就进行后续
		{
			--BounceFrequency;
		}
	}
	else if (OtherActor->ActorHasTag(FName("FlexibleWall")))
	{
		if (!this->ActorHasTag(FName("Sonic")))//不是音波子弹就进行后续
		{
			AFlexibleWall* Flexible = Cast<AFlexibleWall>(OtherActor);
			if (Flexible&& !Flexible->IsLower)//此时没有下降
			{
				Flexible->LowerWall();
				--BounceFrequency;
			}
		}
	}
}

