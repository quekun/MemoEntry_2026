// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TankHeroSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API UTankHeroSaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:
	// 构造函数：用于设置存档创建时的初始默认值
	UTankHeroSaveGame();

public:
	// ===================== 成就数据 =====================

	// 1. 无伤通关记录 (索引 = 关卡序号)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData|Achievements")
	TArray<int32> FlawlessLevels;

	// 2. 不使用道具通关记录 (索引 = 关卡序号)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData|Achievements")
	TArray<int32> NoItemLevels;

	// 3. 速通通关记录 (索引 = 关卡序号)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData|Achievements")
	TArray<int32> SpeedrunLevels;

	// ===================== 设置数据 =====================

	// 3. 三个开关的状态 (比如 0:音乐, 1:音效, 2:相继跟随)
	// 1 表示开，0 表示关
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData|Settings")
	TArray<int32> SwitchStates;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData|Settings")
	int32 MaxLevel;

	void SaveCurrentLevel(bool IsFlawless,bool IsNoItem,bool IsSpeedrun,int CurrentIndex);
};
