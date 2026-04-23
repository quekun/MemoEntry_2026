// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tank.h"
#include "TankHeroGameInstance.h"

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

    UFUNCTION(BlueprintImplementableEvent)
    void UpdateSound();

    UFUNCTION()
    void OnChangeMusicClicked();

    UFUNCTION(BlueprintImplementableEvent)
    void UpdateMusic();

    UFUNCTION()
    void OnChangeFollowCameraClicked();

    UFUNCTION(BlueprintImplementableEvent)
    void UpdateFollowCamera();

    UFUNCTION()
    void OnMainMenuClicked();

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_SoundStatus;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_MusicStatus;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_CameraStatus;

    UTankHeroGameInstance* GameInst;

public:
    // 在蓝图中配置的选关界面类 (槽位)
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UMainMenuWidget> MainMenuWidgetWidgetClass;

    UFUNCTION(BlueprintCallable, Category = "UI")
    void RefreshSettingsUI();
};
