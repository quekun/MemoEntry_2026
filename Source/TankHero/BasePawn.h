// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

class UBoxComponent;


#include "BasePawn.generated.h"

UCLASS()
class TANKHERO_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChassisMesh;

	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HatchMesh;

	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* wheelsMesh;

	

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

};
