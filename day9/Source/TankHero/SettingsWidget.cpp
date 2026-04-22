// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "MainMenuWidget.h"


void USettingsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 绑定点击事件
    if (Btn_ChangeSound)
        Btn_ChangeSound->OnClicked.AddDynamic(this, &USettingsWidget::OnChangeSoundClicked);

    if (Btn_ChangeMusic)
        Btn_ChangeMusic->OnClicked.AddDynamic(this, &USettingsWidget::OnChangeMusicClicked);

    if (Btn_ChangeFollowCamera)
        Btn_ChangeFollowCamera->OnClicked.AddDynamic(this, &USettingsWidget::OnChangeFollowCameraClicked);

    if (Btn_MainMenu)
        Btn_MainMenu->OnClicked.AddDynamic(this, &USettingsWidget::OnMainMenuClicked);
}

void USettingsWidget::OnChangeSoundClicked()
{
    bIsSoundOn = !bIsSoundOn;

    // 2. 根据状态改变文本
    if (Txt_SoundStatus)
    {
        Txt_SoundStatus->SetText(bIsSoundOn?FText::FromString(TEXT("On")): FText::FromString(TEXT("Off")));
    }

    //下面写控制游戏音效具体逻辑
}

void USettingsWidget::OnChangeMusicClicked()
{
    bIsMusicOn = !bIsMusicOn;

    if (Txt_MusicStatus)
    {
        Txt_MusicStatus->SetText(bIsMusicOn ? FText::FromString(TEXT("On")) : FText::FromString(TEXT("Off")));
    }
    //下面写具体逻辑
}

void USettingsWidget::OnChangeFollowCameraClicked()
{
    bIsCameraOn = !bIsCameraOn;

    if (Txt_CameraStatus)
    {
        Txt_CameraStatus->SetText(bIsCameraOn ? FText::FromString(TEXT("On")) : FText::FromString(TEXT("Off")));
    }
    //下面写具体逻辑
}

void USettingsWidget::OnMainMenuClicked()
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
