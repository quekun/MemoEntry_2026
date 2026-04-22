// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"
#include "TankHeroGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UResultWidget::SetupResult(bool bIsWin, float TimeSpent)
{
    if (!bIsWin)
    {
        // 失败情况
        RatingText = TEXT("Needs Improvement");
        bIsNextLevelEnabled = false; // 禁用下一关按钮
    }
    else
    {
        // 胜利情况，判断时间
        bIsNextLevelEnabled = true; // 启用下一关按钮

        if (TimeSpent <= 30.0f)
        {
            RatingText = TEXT("Excellent");
        }
        else if (TimeSpent <= 60.0f)
        {
            RatingText = TEXT("Average");
        }
        else
        {
            RatingText = TEXT("Needs Improvement");
        }
    }
}

void UResultWidget::OnLevelSelectClicked()
{
    // 1. 获取自定义的 GameInstance
    UTankHeroGameInstance* GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());
    if (GameInst)
    {
        // 告诉信使：下一张地图加载好后，直接给我切到选关界面！
        GameInst->bGoDirectlyToLevelSelect = true;
    }

    // 2. 打开主菜单关卡
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UResultWidget::OnNextLevelClicked()
{
    // 1. 获取并转换自定义的 GameInstance
    UTankHeroGameInstance* GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());

    if (GameInst)
    {
        // 2. 计算下一关的索引
        int32 NextIndex = GameInst->CurrentLevelIndex + 1;
        // 3. 安全检查：判断下一关是否超出了关卡列表的最大数量
        if (NextIndex < GameInst->LevelList.Num())
        {
            // 更新实例中的当前索引，让系统知道我们进入了新的一关
            GameInst->CurrentLevelIndex = NextIndex;

            // 根据索引从数组里拿出下一关的地图名字
            FName NextLevelName = GameInst->LevelList[NextIndex];

            // 4. 打开下一关
            UGameplayStatics::OpenLevel(this, NextLevelName);
        }
        else
        {
            // 如果已经是最后一关了（或者数组没填），可以直接返回主菜单
            // 顺便把状态设为返回选关界面（复用之前的暗号！）
            GameInst->bGoDirectlyToLevelSelect = true;
            UGameplayStatics::OpenLevel(this, FName("MainMenu")); // 替换为你的主菜单地图名
        }
    }
}

void UResultWidget::OnRestartClicked()
{
    // 获取当前关卡的名字并重新打开
    FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this, true);
    UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}
