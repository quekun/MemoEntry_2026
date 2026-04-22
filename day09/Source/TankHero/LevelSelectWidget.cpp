// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelectWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h" // 用于退出游戏等
#include "Kismet/GameplayStatics.h"
#include "MainMenuWidget.h"

void ULevelSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();
    // 绑定点击事件
    if (Btn_Level1)
        Btn_Level1->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnLevel1Clicked);

    if (Btn_Level2)
        Btn_Level2->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnLevel2Clicked);

    if (Btn_Level3)
        Btn_Level3->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnLevel3Clicked);

    if (Btn_MainMenu)
        Btn_MainMenu->OnClicked.AddDynamic(this, &ULevelSelectWidget::OnMainMenuClicked);
}

void ULevelSelectWidget::OnLevel1Clicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("TestLevel"));
}

void ULevelSelectWidget::OnLevel2Clicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("TestLevel1"));
}

void ULevelSelectWidget::OnLevel3Clicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("TestLevel2"));
}

void ULevelSelectWidget::OnMainMenuClicked()
{
    if (MainMenuWidgetWidgetClass)
    {
        // 2. 创建选关界面的实例
        UMainMenuWidget* MainMenuMenu = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetWidgetClass);

        if (MainMenuMenu)
        {
            // 3. 把选关界面添加到屏幕上
            MainMenuMenu->AddToViewport();

            // 4. 把当前的主界面自己从屏幕上销毁掉
            this->RemoveFromParent();
        }
    }
}
