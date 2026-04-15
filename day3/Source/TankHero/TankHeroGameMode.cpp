// Copyright Epic Games, Inc. All Rights Reserved.

#include "TankHeroGameMode.h"
#include "Enemy.h"
//#include "ScreenMessage.h"

ATankHeroGameMode::ATankHeroGameMode()
{
	// stub
}

void ATankHeroGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Enemies;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Enemies);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	EnemyCount = Enemies.Num();

	if (PlayerPawn)
	{
		Tank = Cast<ATank>(PlayerPawn);

		if (!Tank)
		{
			UE_LOG(LogTemp, Display, TEXT("Cast error"));
		}
	}

	for (auto& LoopEnemy : Enemies)
	{
		AEnemy* Enemy = Cast<AEnemy>(LoopEnemy);
		if (Enemy && Tank)
		{
			Enemy->Tank = Tank;
		}
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		UE_LOG(LogTemp, Display, TEXT("Get Ready!"));
		/*ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayerController, ScreenMessageClass);
		if (ScreenMessageWidget)
		{
			ScreenMessageWidget->AddToPlayerScreen();
			ScreenMessageWidget->SetMessageText("Get Ready!");
		}*/
	}
	CountdownSeconds = CountdownDelay;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
		&ATankHeroGameMode::OnCountdownTimerTimeout, 1, true);
}

void ATankHeroGameMode::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;

	if (DeadActor == Tank)
	{
		IsGameOver = true;
		Tank->HandleDestruction();
	}
	else
	{
		AEnemy* DeadEnemy = Cast<AEnemy>(DeadActor);
		if (DeadEnemy)
		{
			DeadEnemy->HandleDestruction();
			EnemyCount--;
		}
		if (!EnemyCount)
		{
			IsGameOver = true;
			IsVictory = true;
		}
	}
	if (IsGameOver)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), IsVictory ? TEXT("Victory") : TEXT("Defeat"));
		/*ScreenMessageWidget->SetMessageText(IsVictory ? TEXT("Victory") : TEXT("Defeat"));
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);*/
		FTimerHandle GameOverTimeHandle;
		GetWorldTimerManager().SetTimer(GameOverTimeHandle, this, &ATankHeroGameMode::OnGameOverTimerTimeout, GameOverDelay, false);

	}
}

void ATankHeroGameMode::OnGameOverTimerTimeout()
{
	UE_LOG(LogTemp, Display, TEXT("GameOver"));
	/*UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UTankHeroGameInstance* TankHeroGameInstance = Cast<UTankHeroGameInstance>(GameInstance);
		if (TankHeroGameInstance)
		{
			if (IsVictory)
			{
				TankHeroGameInstance->LoadNextLevel();
			}
			else
			{
				TankHeroGameInstance->RestartGame();
			}
		}
	}*/
}

void ATankHeroGameMode::OnCountdownTimerTimeout()
{
	if (CountdownSeconds > 0)
	{
		//ScreenMessageWidget->SetMessageText(FString::FromInt(CountdownSeconds));
		UE_LOG(LogTemp, Display, TEXT("%d"), CountdownSeconds);
	}
	else if (CountdownSeconds == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Go!"));
		//ScreenMessageWidget->SetMessageText("Go!");
		Tank->SetPlayerEnabled(true);
	}
	else
	{
		//ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
	CountdownSeconds--;
}
