// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "TankHeroGameInstance.h"



void UHUDWidget::SetHealthBarPercent(float CurrentHealth, float MaxHealth)
{
	if (CurrentHealth <= 0.f || MaxHealth<=0.f)
	{
		return;
	}
	if (!HealthBar)
	{
		return;
	}
	float HealthPercent = CurrentHealth / MaxHealth;
	HealthBar->SetPercent(HealthPercent);

	// 4. 根据百分比变色逻辑
	FLinearColor BarColor;
	if (HealthPercent >= 0.6f)       // 60% 到 100%
	{
		BarColor = FLinearColor::Green;
	}
	else if (HealthPercent >= 0.3f)  // 30% 到 60%
	{
		BarColor = FLinearColor::Yellow;
	}
	else                             // 30% 以下
	{
		BarColor = FLinearColor::Red;
	}

	// 5. 将计算好的颜色应用到进度条上
	HealthBar->SetFillColorAndOpacity(BarColor);
}

UTexture2D* UHUDWidget::GetCurrentLevelImage()
{
	UTankHeroGameInstance* GameInst = Cast<UTankHeroGameInstance>(GetGameInstance());
	if (GameInst)
	{
		// 用当前的关卡索引去拿贴图
		int32 Index = GameInst->CurrentLevelIndex;
		if (GameInst->LevelImages.IsValidIndex(Index))
		{
			return GameInst->LevelImages[Index];
		}
	}
	return nullptr;
}
