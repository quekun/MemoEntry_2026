// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"


class UScreenMessage;


#include "TankHeroGameMode.generated.h"

/**
 *  Simple Game Mode for a top-down perspective game
 *  Sets the default gameplay framework classes
 *  Check the Blueprint derived class for the set values
 */
UCLASS(abstract)
class ATankHeroGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	/** Constructor */
	ATankHeroGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATank* Tank;

	/*UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;

	UScreenMessage* ScreenMessageWidget;*/

	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.f;

	UPROPERTY(EditAnywhere)
	float CountdownDelay = 3.f;

	int32 CountdownSeconds;

	FTimerHandle CountdownTimerHandle;

	int32 EnemyCount;

	bool IsVictory = false;

	void ActorDied(AActor* DeadActor);

	void OnGameOverTimerTimeout();

	void OnCountdownTimerTimeout();


};



