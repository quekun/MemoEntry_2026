// Copyright Epic Games, Inc. All Rights Reserved.

#include "TankHeroGameMode.h"
#include "Enemy.h"
#include "EnemyAl_New.h"
#include "Kismet/GameplayStatics.h"
#include "ResultWidget.h"
#include "Blueprint/UserWidget.h" 
#include "TankHeroGameInstance.h"
//#include "ScreenMessage.h"

ATankHeroGameMode::ATankHeroGameMode()
{
	// stub
}

void ATankHeroGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		LevelStartTime = GetWorld()->GetTimeSeconds();
	}

	if (HUDWidgetClass) // 安全检查：确保你在蓝图里选了UI类
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UUserWidget* HUDWidget = CreateWidget<UUserWidget>(PC, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}

	TArray<AActor*> EnemyAls;
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Enemies);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAl_New::StaticClass(), EnemyAls);

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	EnemyCount = Enemies.Num();

	if (Player)
	{
		Tank = Cast<ATank>(Player);

		if (Tank)
		{
			for (auto& LoopEnemyAl : EnemyAls)
			{
				AEnemyAl_New* EnemyAl = Cast<AEnemyAl_New>(LoopEnemyAl);
				if (EnemyAl)
				{
					EnemyAl->StartBehaviorTree(Tank);
					UE_LOG(LogTemp, Display, TEXT("name is %s"), *EnemyAl->GetActorNameOrLabel());
				}
			}
		}
	}

	for (auto& LoopEnemy : Enemies)
	{
		AEnemy* Enemy = Cast<AEnemy>(LoopEnemy);
		if (Enemy && Tank)
		{
			Enemy->Tank = Tank;
		}
	}
}

void ATankHeroGameMode::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;

	if (DeadActor == Tank)
	{
		IsGameOver = true;
		Tank->HandleDestruction();
	}
	else
	{
		AEnemy* DeadEnemy = Cast<AEnemy>(DeadActor);
		if (DeadEnemy)
		{
			DeadEnemy->HandleDestruction();
			EnemyCount--;
		}
		if (!EnemyCount)
		{
			IsGameOver = true;
			IsVictory = true;
		}
	}
	if (IsGameOver)
	{
		UTankHeroGameInstance* GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());

		int32 NextLevelIndex = GameInst->CurrentLevelIndex + 1;

		if (NextLevelIndex > GameInst->MaxUnlockedLevelIndex && NextLevelIndex < GameInst->LevelList.Num())
		{
			GameInst->MaxUnlockedLevelIndex = NextLevelIndex;
		}

		// 1. 暂停游戏世界时间
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// 先获取玩家控制器
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		// 创建 UI，把 PC 传进去作为拥有者
		UResultWidget* ResultWidget = CreateWidget<UResultWidget>(PC, ResultWidgetClass);
		if (ResultWidget)
		{
			ResultWidget->SetupResult(IsVictory, GetTimeSpent());
			ResultWidget->AddToViewport();
		}

		// 设置鼠标和输入模式
		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeUIOnly());
		}
	}
}

float ATankHeroGameMode::GetTimeSpent() const
{
	if (GetWorld())
	{
		return GetWorld()->GetTimeSeconds() - LevelStartTime;
	}
	return 0.0f;
}
