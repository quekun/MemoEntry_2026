// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h" // 用于退出游戏等
#include "Kismet/GameplayStatics.h"
#include "LevelSelectWidget.h"
#include "SettingsWidget.h"
#include "TankHeroGameInstance.h"


void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 绑定点击事件
    if (Btn_LevelSelect)
        Btn_LevelSelect->OnClicked.AddDynamic(this, &UMainMenuWidget::OnLevelSelectClicked);

    if (Btn_Settings)
        Btn_Settings->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);

    if (Btn_Quit)
        Btn_Quit->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);

    if (Btn_Save)
        Btn_Save->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSaveClicked);

    if (Btn_Load)
        Btn_Load->OnClicked.AddDynamic(this, &UMainMenuWidget::OnLoadClicked);
}

void UMainMenuWidget::OnLevelSelectClicked()
{
    // 1. 确保你在蓝图中已经配置了这个类，防止空指针崩溃
    if (LevelSelectWidgetClass)
    {
        // 2. 创建选关界面的实例
        ULevelSelectWidget* LevelSelectMenu = CreateWidget<ULevelSelectWidget>(GetWorld(), LevelSelectWidgetClass);

        if (LevelSelectMenu)
        {
            // 3. 把选关界面添加到屏幕上
            LevelSelectMenu->AddToViewport();

            // 4. 把当前的主界面自己从屏幕上销毁掉
            this->RemoveFromParent();
        }
    }
}


void UMainMenuWidget::OnSettingsClicked()
{
    if (SettingsWidgetClass)
    {
        // 2. 创建选关界面的实例
        USettingsWidget* SettingsMenu = CreateWidget<USettingsWidget>(GetWorld(), SettingsWidgetClass);

        if (SettingsMenu)
        {
            // 3. 把选关界面添加到屏幕上
            SettingsMenu->AddToViewport();

            // 4. 把当前的主界面自己从屏幕上销毁掉
            this->RemoveFromParent();
        }
    }
}

void UMainMenuWidget::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), 
        EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnSaveClicked()
{
    UTankHeroGameInstance* GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());
    if (GameInst && GameInst->CurrentSaveGame)
    {
        int32 SlotIndex = 1;
        FString CurrentSlotName = FString::Printf(TEXT("Slot%d"), SlotIndex); // 拼出 "Slot1"

        // 只要这个名字的存档已经存在，我们就试下一个数字 (Slot2, Slot3...)
        while (UGameplayStatics::DoesSaveGameExist(CurrentSlotName, 0))
        {
            SlotIndex++; // 数字+1
            CurrentSlotName = FString::Printf(TEXT("Slot%d"), SlotIndex); // 重新拼名字
        }

        //存入
        bool bIsSaved = UGameplayStatics::SaveGameToSlot(GameInst->CurrentSaveGame, CurrentSlotName, 0);

        if (bIsSaved)
        {
            FString SuccessMsg = FString::Printf(TEXT("Save Succeed! Slot No.%s"), *CurrentSlotName);
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, SuccessMsg);
        }
    }
}


void UMainMenuWidget::OnLoadClicked()
{
    // 1. 获取 GameInstance
    UTankHeroGameInstance* GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());

    if (GameInst)
    {
        // 指定读取的指定存档名字
        FString SlotNameToLoad = TEXT("Slot1");

        // 严谨一点，先检查硬盘里到底有没有这个存档文件
        if (UGameplayStatics::DoesSaveGameExist(SlotNameToLoad, 0))
        {
            // 3从硬盘读取存档，并转换为存档类
            UTankHeroSaveGame* LoadedData = Cast<UTankHeroSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotNameToLoad, 0));

            if (LoadedData)
            {
                // 4. 
                // 将 GameInstance 当前持有的存档指针，替换为刚读取出来的这个完整对象。
                // 替换后，GameInst 里面的三个数组自动就变成硬盘里的旧数据了，不需要手动一个一个赋值
                GameInst->CurrentSaveGame = LoadedData;

                // 打印成功提示
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Load Succeed!"));
            }
        }
        else
        {
            // 如果硬盘里根本没有这个文件
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Fail to find "));
        }

        GameInst->MaxUnlockedLevelIndex = GameInst->CurrentSaveGame->MaxLevel;
        GameInst->bIsSoundOn = (GameInst->CurrentSaveGame->SwitchStates[0] != 0);
        GameInst->bIsMusicOn = (GameInst->CurrentSaveGame->SwitchStates[1] != 0);
        GameInst->bIsCameraFollowOn = (GameInst->CurrentSaveGame->SwitchStates[2] != 0);
        
    }

}
