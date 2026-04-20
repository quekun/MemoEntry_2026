// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBall.h"

#include "Tank.h"
AWeaponBall::AWeaponBall()
{

}

void AWeaponBall::GetEffect(ATank* Tank)
{
	Tank->SetNewBullet(BulletClass);
	Destroy();
}


