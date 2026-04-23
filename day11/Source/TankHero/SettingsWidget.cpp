// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "MainMenuWidget.h"
#include "TankHeroSaveGame.h"

void USettingsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());
    // 绑定点击事件
    if (Btn_ChangeSound)
        Btn_ChangeSound->OnClicked.AddDynamic(this, &USettingsWidget::OnChangeSoundClicked);

    if (Btn_ChangeMusic)
        Btn_ChangeMusic->OnClicked.AddDynamic(this, &USettingsWidget::OnChangeMusicClicked);

    if (Btn_ChangeFollowCamera)
        Btn_ChangeFollowCamera->OnClicked.AddDynamic(this, &USettingsWidget::OnChangeFollowCameraClicked);

    if (Btn_MainMenu)
        Btn_MainMenu->OnClicked.AddDynamic(this, &USettingsWidget::OnMainMenuClicked);

    if(Txt_SoundStatus)
        Txt_SoundStatus->SetText(GameInst->bIsSoundOn ? FText::FromString(TEXT("On")) : FText::FromString(TEXT("Off")));

    if(Txt_MusicStatus)
        Txt_MusicStatus->SetText(GameInst->bIsMusicOn ? FText::FromString(TEXT("On")) : FText::FromString(TEXT("Off")));

    if(Txt_CameraStatus)
        Txt_CameraStatus->SetText(GameInst->bIsCameraFollowOn ? FText::FromString(TEXT("On")) : FText::FromString(TEXT("Off")));

    
    UpdateSound();
    
}

void USettingsWidget::OnChangeSoundClicked()
{
    if (GameInst)
    {
        GameInst->bIsSoundOn = !GameInst->bIsSoundOn;
        if (GameInst->CurrentSaveGame)
        {
            GameInst->CurrentSaveGame->SwitchStates[0] = GameInst->bIsSoundOn;
        }
        // 2. 根据状态改变文本
        if (Txt_SoundStatus)
        {
            Txt_SoundStatus->SetText(GameInst->bIsSoundOn ? FText::FromString(TEXT("On")) : FText::FromString(TEXT("Off")));
            UpdateSound();
        }
        //控制游戏音效具体逻辑在蓝图中实现
        
    } 
}


void USettingsWidget::OnChangeMusicClicked()
{
    if (GameInst)
    {
        GameInst->bIsMusicOn = !GameInst->bIsMusicOn;
        if (GameInst->CurrentSaveGame)
        {
            GameInst->CurrentSaveGame->SwitchStates[1] = GameInst->bIsMusicOn;
        }

        if (Txt_MusicStatus)
        {
            Txt_MusicStatus->SetText(GameInst->bIsMusicOn ? FText::FromString(TEXT("On")) : FText::FromString(TEXT("Off")));
            UpdateMusic();
        }
        
    }
}

void USettingsWidget::OnChangeFollowCameraClicked()
{
    if (GameInst)
    {
        GameInst->bIsCameraFollowOn = !GameInst->bIsCameraFollowOn;
        if (GameInst->CurrentSaveGame)
        {
            GameInst->CurrentSaveGame->SwitchStates[2] = GameInst->bIsCameraFollowOn;
        }

        if (Txt_CameraStatus)
        {
            Txt_CameraStatus->SetText(GameInst->bIsCameraFollowOn ? FText::FromString(TEXT("On")) : FText::FromString(TEXT("Off")));
            UpdateFollowCamera();
        }
        
    }
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

void USettingsWidget::RefreshSettingsUI()
{

    
}
