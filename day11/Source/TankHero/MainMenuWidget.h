// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class USettingsWidget;
class ULevelSelectWidget;
class UButton;

/**
 * 
 */
UCLASS()
class TANKHERO_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
    virtual void NativeConstruct() override; // 相当于蓝图的 BeginPlay

    // 重点：使用 BindWidget，变量名必须和未来蓝图中按钮的命名一模一样！
    UPROPERTY(meta = (BindWidget))
    UButton* Btn_LevelSelect;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Settings;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Quit;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Save;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Load;

    // 按钮点击响应函数
    UFUNCTION()
    void OnLevelSelectClicked();

    UFUNCTION()
    void OnSettingsClicked();

    UFUNCTION()
    void OnQuitClicked();

    UFUNCTION()
    void OnSaveClicked();

    UFUNCTION()
    void OnLoadClicked();


public:
    // 在蓝图中配置的选关界面类 (槽位)
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class ULevelSelectWidget> LevelSelectWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class USettingsWidget> SettingsWidgetClass;
};
