// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelectWidget.generated.h"

class UMainMenuWidget;
class UButton;
/**
 * 
 */
UCLASS()
class TANKHERO_API ULevelSelectWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    virtual void NativeConstruct() override; // 相当于蓝图的 BeginPlay

    // 重点：使用 BindWidget，变量名必须和未来蓝图中按钮的命名一模一样！
    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Level1;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Level2;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Level3;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_MainMenu;

    // 按钮点击响应函数
    UFUNCTION()
    void OnLevel1Clicked();

    UFUNCTION()
    void OnLevel2Clicked();

    UFUNCTION()
    void OnLevel3Clicked();

    UFUNCTION()
    void OnMainMenuClicked();

public:
    // 在蓝图中配置的选关界面类 (槽位)
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UMainMenuWidget> MainMenuWidgetWidgetClass;
};
