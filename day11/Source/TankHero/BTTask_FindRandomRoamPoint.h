// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindRandomRoamPoint.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API UBTTask_FindRandomRoamPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FindRandomRoamPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;

	UPROPERTY(EditAnywhere)
	float Radius;
};
