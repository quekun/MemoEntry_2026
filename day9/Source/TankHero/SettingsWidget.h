// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

class UMainMenuWidget;
class UButton;
/**
 * 
 */
UCLASS()
class TANKHERO_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override; // 相当于蓝图的 BeginPlay

    // 重点：使用 BindWidget，变量名必须和未来蓝图中按钮的命名一模一样！
    UPROPERTY(meta = (BindWidget))
    UButton* Btn_ChangeSound;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_ChangeMusic;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_ChangeFollowCamera;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_MainMenu;


    // 按钮点击响应函数
    UFUNCTION()
    void OnChangeSoundClicked();

    UFUNCTION()
    void OnChangeMusicClicked();

    UFUNCTION()
    void OnChangeFollowCameraClicked();

    UFUNCTION()
    void OnMainMenuClicked();

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_SoundStatus;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_MusicStatus;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_CameraStatus;

    // ================= 新增：记录状态的变量 =================
    bool bIsSoundOn = true;
    bool bIsMusicOn = true;
    bool bIsCameraOn = true;

public:
    // 在蓝图中配置的选关界面类 (槽位)
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UMainMenuWidget> MainMenuWidgetWidgetClass;
};
