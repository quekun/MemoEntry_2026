// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		AActor* MyOwner = GetOwner();
		if (MyOwner && OtherActor != MyOwner && OtherActor != this)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(),
				this, UDamageType::StaticClass());
		}
		Destroy();
	}
}

