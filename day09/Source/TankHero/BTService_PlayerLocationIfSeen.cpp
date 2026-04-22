// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "EnemyAl_New.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tank.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update PlayerLocation If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemyAl_New* OwnerController = Cast<AEnemyAl_New>(OwnerComp.GetAIOwner());
	if (OwnerController)
	{
		ATank* Tank = Cast<ATank>(OwnerController->PlayerPawn);
		UBlackboardComponent* BlackboardComp = OwnerController->GetBlackboardComponent();
		if (Tank && BlackboardComp)
		{
			if (OwnerController->LineOfSightTo(Tank))
			{
				BlackboardComp->SetValueAsVector(PlayerLocationKey.SelectedKeyName, Tank->GetActorLocation());
				BlackboardComp->SetValueAsVector(LastKnownPlayerLocationKey.SelectedKeyName, Tank->GetActorLocation());
				OwnerController->SetFocus(Tank);
			}
			else
			{
				BlackboardComp->ClearValue(PlayerLocationKey.SelectedKeyName);
				OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
			}
		}
	}
	
}
