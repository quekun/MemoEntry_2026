// Fill out your copyright notice in the Description page of Project Settings.


#include "TankHeroSaveGame.h"

UTankHeroSaveGame::UTankHeroSaveGame()
{
    // 初始化三个开关，默认都为 1 (开启)
    SwitchStates.Init(1, 3);

    // 全部初始化为 0
    FlawlessLevels.Init(0, 3);
    NoItemLevels.Init(0, 3);
    SpeedrunLevels.Init(0,3);
    MaxLevel = 0;
}

void UTankHeroSaveGame::SaveCurrentLevel(bool IsFlawless, bool IsNoItem, bool IsSpeedrun,  int CurrentIndex)
{
    FlawlessLevels[CurrentIndex] = IsFlawless;
    NoItemLevels[CurrentIndex] = IsNoItem;
    SpeedrunLevels[CurrentIndex] = IsSpeedrun;
    
}
