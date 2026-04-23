// Fill out your copyright notice in the Description page of Project Settings.


#include "TankHeroGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UTankHeroGameInstance::Init()
{
    // 一定要先调用父类的 Init
    Super::Init();

    // 1. 先检查是不是有旧存档？
    CurrentSaveGame = Cast<UTankHeroSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TankHeroSave"), 0));

    // 2. 如果 CurrentSaveGame 是空的（玩家第一次玩，没找到旧房子）
    if (CurrentSaveGame == nullptr)
    {
        // 3. 拿出你在编辑器里选好的图纸 (SaveGameClass)
        if (SaveGameClass != nullptr)
        {
            // 4. 按照图纸，凭空造一个新房子出来！并把钥匙交给 CurrentSaveGame
            CurrentSaveGame = Cast<UTankHeroSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));
        }
    }
}
