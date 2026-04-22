// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffBall.h"
#include "Tank.h"

ABuffBall::ABuffBall()
{

}

void ABuffBall::GetEffect(ATank* Tank)
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *GetActorNameOrLabel());
	for (const FName& OneTag : this->Tags)
	{
		UE_LOG(LogTemp, Display, TEXT("content: %s"), *OneTag.ToString());
	}
	if (this->ActorHasTag(FName("BounceBall")))
	{
		Tank->BounceUpStart();
	}
	else if (this->ActorHasTag(FName("BoostSpeedBall")))
	{
		Tank->BoostSpeedStart();
	}
	else
	{
		Tank->ShieldStart();
	}
	Destroy();
}
