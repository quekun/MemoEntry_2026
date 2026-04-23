// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"
#include "TankHeroGameMode.generated.h"

/**
 *  Simple Game Mode for a top-down perspective game
 *  Sets the default gameplay framework classes
 *  Check the Blueprint derived class for the set values
 */
UCLASS(abstract)
class ATankHeroGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	/** Constructor */
	ATankHeroGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 记录关卡开始时间的变量
	float LevelStartTime;

	// 游戏是否已经结束的标志
	bool bHasGameEnded = false;

public:
	ATank* Tank;

	// 用来在蓝图里选择你的 WBP_HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> HUDWidgetClass; // 这里写 UUserWidget 就行，包含头文件方便

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* BGMMusic;

	int32 EnemyCount;

	bool IsVictory = false;

	void ActorDied(AActor* DeadActor);

	// 处理游戏结束延迟后的UI和暂停逻辑
	void HandleGameOverDelay();

	UFUNCTION(BlueprintPure, Category = "Level Timer")
	float GetTimeSpent() const;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UResultWidget> ResultWidgetClass;
};



