// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class TANKHERO_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Resume; // 继续游戏按钮

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_NextLevel; 

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_SelectLevel;

    UFUNCTION()
    void OnResumeClicked();

    UFUNCTION()
    void OnNextLevelClicked();

    UFUNCTION()
    void OnSelectLevelClicked();

public:
    // 在蓝图中配置的选关界面类 (槽位)
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class ULevelSelectWidget> LevelSelectWidgetClass;
};
