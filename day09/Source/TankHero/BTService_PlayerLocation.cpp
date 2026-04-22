// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "EnemyAl_New.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Update LastPlayerLocation If Seen");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AEnemyAl_New* OwnerController = Cast<AEnemyAl_New>(OwnerComp.GetAIOwner());
	if (OwnerController)
	{
		ATank* Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		UBlackboardComponent* Blackboard = OwnerController->GetBlackboardComponent();
		if (Tank && Blackboard)
		{
			Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Tank->GetActorLocation());
		}
	}
}
