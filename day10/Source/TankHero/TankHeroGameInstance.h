// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TankHeroGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API UTankHeroGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    // 用来标记进入主菜单关卡时，是否直接显示选关界面
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI State")
    bool bGoDirectlyToLevelSelect = false;

public:
    // 存放所有关卡名字的数组（注意顺序就是通关顺序）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level System")
    TArray<FName> LevelList;

    // 当前正在玩的关卡索引（0代表第一关）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level System")
    int32 CurrentLevelIndex = 0;

    // 存放每一关开场提示贴图的数组 (顺序要和 LevelList 完全对应)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level System")
    TArray<UTexture2D*> LevelImages;

    // 记录玩家当前解锁到的最大关卡索引（默认 0，代表只解锁了第1关）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level System")
    int32 MaxUnlockedLevelIndex = 0;
};
