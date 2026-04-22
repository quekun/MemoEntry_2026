// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h" // 用于退出游戏等
#include "Kismet/GameplayStatics.h"
#include "LevelSelectWidget.h"
#include "SettingsWidget.h"

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
