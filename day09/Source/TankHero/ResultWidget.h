// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // --- 供蓝图绑定的显示数据 ---

    // 最终的评分文本 (Excellent, Average, Needs Improvement)
    UPROPERTY(BlueprintReadOnly, Category = "Settlement UI")
    FString RatingText;

    // 是否允许点击“下一关”按钮
    UPROPERTY(BlueprintReadOnly, Category = "Settlement UI")
    bool bIsNextLevelEnabled;

    // --- 核心逻辑函数 ---

    // 初始化结算界面时调用，传入是否胜利和消耗的时间（秒）
    UFUNCTION(BlueprintCallable, Category = "Result Logic")
    void SetupResult(bool bIsWin, float TimeSpent);

    // --- 三个按钮的点击事件 ---
    UFUNCTION(BlueprintCallable, Category = "Settlement Logic")
    void OnLevelSelectClicked();

    UFUNCTION(BlueprintCallable, Category = "Settlement Logic")
    void OnNextLevelClicked();

    UFUNCTION(BlueprintCallable, Category = "Settlement Logic")
    void OnRestartClicked();

};
