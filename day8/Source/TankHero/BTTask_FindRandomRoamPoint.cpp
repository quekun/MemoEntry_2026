#include "BTTask_FindRandomRoamPoint.h"
#include "EnemyAl_New.h"
#include "Tank.h"
#include "Enemy.h"
#include "NavigationSystem.h" 
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_FindRandomRoamPoint::UBTTask_FindRandomRoamPoint()
{
	NodeName = TEXT("Find Random RoamPoint");
	Radius = 1000.f;
}

EBTNodeResult::Type UBTTask_FindRandomRoamPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 获取 AI 控制器和受控的 Enemy Pawn
	AEnemyAl_New* OwnerController = Cast<AEnemyAl_New>(OwnerComp.GetAIOwner());
	if (!OwnerController || !OwnerController->MyPawn)
	{
		return EBTNodeResult::Failed; // 如果没获取到，任务失败
	}

	AEnemy* Enemy = OwnerController->MyPawn;
	FVector OriginLocation = Enemy->GetActorLocation(); // 以坦克当前位置为中心

	// 1. 获取当前世界的导航系统
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSystem)
	{
		FNavLocation RandomReachableLocation;

		// 2. 核心代码：获取半径内的随机可到达点
		// 参数：起点位置，搜索半径，用于存放结果的变量
		bool bFoundPoint = NavSystem->GetRandomReachablePointInRadius(OriginLocation, Radius, RandomReachableLocation);

		if (bFoundPoint)
		{
			// 3. 拿到黑板组件
			UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
			if (BlackboardComp)
			{
				// 4. 将获取到的随机点坐标，写入到黑板的 "RoamLocation" 键中
				// 注意：这里的名字必须和你黑板里建的那个 Vector 变量名一模一样！
				BlackboardComp->SetValueAsVector(TEXT("RoamLocation"), RandomReachableLocation.Location);

				return EBTNodeResult::Succeeded; // 成功找到并写入，任务完成
			}
		}
	}

	// 如果没有导航网格或者没找到点，返回失败
	return EBTNodeResult::Failed;
}
