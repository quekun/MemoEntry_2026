// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "Navigation/PathFollowingComponent.h"

#include "EnemyAl_New.generated.h"


class ATank;
class AEnemy;

UCLASS()
class TANKHERO_API AEnemyAl_New : public ADetourCrowdAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAl_New();

	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:


	FTimerHandle TimerHandle_MoveUpdate;

	void UpdateMove();

	UPROPERTY(EditAnywhere)
	float Radius = 200.f;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyBehaviorTree;

	ATank* PlayerPawn;
	AEnemy* MyPawn;

	void StartBehaviorTree(ATank* Player);
};
