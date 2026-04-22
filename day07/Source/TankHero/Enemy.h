// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"



class ATank;
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API AEnemy : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TrackMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Barrel_LMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Barrel_RMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HullMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ArmorSkirtMesh;

	ATank* Tank;

	FVector LastLocation;

	float StuckTime = 0.f;

	UPROPERTY(EditAnywhere)
	float HullRotateRate = 10.f;

	void HandleDestruction();

	void RotateHull(FVector LookAtTarget);

	virtual void Fire();

};
