// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSelectWidget.h"
#include "TankHeroGameInstance.h"

void UPauseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (Btn_Resume)
        Btn_Resume->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeClicked);
    if(Btn_SelectLevel)
        Btn_SelectLevel->OnClicked.AddDynamic(this, &UPauseWidget::OnSelectLevelClicked);
    if(Btn_NextLevel)
        Btn_NextLevel->OnClicked.AddDynamic(this, &UPauseWidget::OnNextLevelClicked);

    GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());

    RefreshPauseUI();
}

void UPauseWidget::OnResumeClicked()
{
    // 1. 恢复游戏时间（取消暂停）
    UGameplayStatics::SetGamePaused(GetWorld(), false);

    // 2. 获取玩家控制器，隐藏鼠标，把输入模式改回“仅游戏”
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }

    // 3. 销毁暂停界面自己
    this->RemoveFromParent();
}

void UPauseWidget::OnNextLevelClicked()
{

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

void UPauseWidget::OnSelectLevelClicked()
{

    if (GameInst)
    {
        // 告诉信使：下一张地图加载好后，直接给我切到选关界面！
        GameInst->bGoDirectlyToLevelSelect = true;
    }

    // 2. 打开主菜单关卡
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UPauseWidget::RefreshPauseUI()
{
    if (!GameInst) return;

    if (Btn_NextLevel)
        Btn_NextLevel->SetIsEnabled(GameInst->CurrentSaveGame->MaxLevel >= GameInst->CurrentLevelIndex);
}
