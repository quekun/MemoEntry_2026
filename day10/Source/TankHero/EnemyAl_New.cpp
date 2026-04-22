// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAl_New.h"
#include "Tank.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAl_New::AEnemyAl_New()
{

}



void AEnemyAl_New::BeginPlay()
{
	Super::BeginPlay();
	//PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//if (PlayerPawn)
	//{
	//	SetFocus(PlayerPawn); // 保持朝向

	//	 每 0.5 秒执行一次 UpdateMove，true表示循环执行
	//	GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveUpdate, this, &AEnemyAl::UpdateMove, 0.2f, true);
	//}
}

void AEnemyAl_New::UpdateMove()
{
	if (PlayerPawn)
	{
		// 每半秒寻路一次，给浮动组件留出加速和移动的时间

		/*if (LineOfSightTo(PlayerPawn))
		{
			SetFocus(PlayerPawn);
			MoveToActor(PlayerPawn, Radius);
		}
		else
		{
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}*/
	}

}

void AEnemyAl_New::StartBehaviorTree(ATank* Player)
{
	if (EnemyBehaviorTree)
	{
		MyPawn = Cast<AEnemy>(GetPawn());
		if (Player)
		{
			PlayerPawn = Player;
		}
		RunBehaviorTree(EnemyBehaviorTree);
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		if (BlackboardComponent && Player && MyPawn)
		{
			BlackboardComponent->SetValueAsVector("PlayerLocation", Player->GetActorLocation());
			BlackboardComponent->SetValueAsVector("StartLocation", MyPawn->GetActorLocation());
		}
	}

}

void AEnemyAl_New::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Tick 里面什么寻路都不要写！
}
