// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Fire.h"
#include "EnemyAl_New.h"
#include "Tank.h"
#include "Enemy.h"

UBTTaskNode_Fire::UBTTaskNode_Fire()
{
	NodeName = TEXT("Fire At Player");
}

EBTNodeResult::Type UBTTaskNode_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AEnemyAl_New* OwnerController = Cast<AEnemyAl_New>(OwnerComp.GetAIOwner());
	if (OwnerController)
	{
		ATank* Tank = OwnerController->PlayerPawn;
		AEnemy* Enemy = OwnerController->MyPawn;
		if (Tank && Enemy && Tank->IsAlive)
		{
			Enemy->Fire();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
