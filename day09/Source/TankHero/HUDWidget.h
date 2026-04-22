// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"

#include "HUDWidget.generated.h"
/**
 * 
 */
UCLASS()
class TANKHERO_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,meta=(BindWidgetOptional))
	UProgressBar* HealthBar;


	void SetHealthBarPercent(float CurrentHealth,float MaxHealth);

	// 获取当前关卡对应的开场贴图
	UFUNCTION(BlueprintCallable, Category = "HUD")
	UTexture2D* GetCurrentLevelImage();
};
