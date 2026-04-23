// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"


#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

class UInputAction;
class UInputMappingContext;

class UShieldComponent;

#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenShield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseShield);

UCLASS()
class TANKHERO_API ATank : public ABasePawn
{
	GENERATED_BODY()
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// 记录车身初始相对变换
	FVector BaseChassisLoc;
	FRotator BaseChassisRot;


public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOpenShield OnOpenShield;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCloseShield OnCloseShield;

public:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Track_LMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Track_RMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ExhaustMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AntennaMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* PauseGameAction;

	UPROPERTY(EditAnywhere)
	float MoveShake = 20.0f;

	UPROPERTY(EditAnywhere)
	float TurnShake = 15.0f;

	UPROPERTY(EditAnywhere)
	float Speed = 300.0f;

	UPROPERTY(EditAnywhere)
	float TurnRate = 70.0f;

	UPROPERTY(EditAnywhere)
	float CameraHeight = 30.f;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> FireCameraShakeClass;

	UPROPERTY(EditAnywhere)
	UShieldComponent* ShieldComp;

	FVector MeshInternalOrigin;

	FVector CurrentRecoilOffset;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RecoilStrength = 50.f; // 后坐力强度

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RecoilRestoreSpeed = 15.f; // 复位速度

	UPROPERTY(EditAnywhere, Category = "Movement")
	float BounceUpDuration = 5.0f; // 指定的时间间隔

	UPROPERTY(EditAnywhere, Category = "Movement")
	float BoostSpeedDuration = 5.0f; // 指定的时间间隔

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ShieldDuration = 5.0f; // 指定的时间间隔

	UPROPERTY(EditAnywhere)
	float TurretRotateRate = 10.0f; 

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraFollow(bool bFollow);


	FVector	DefaultLoc ;
	FRotator DefaultRot ;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	APlayerController* PlayerController;

	virtual void Fire();

	void TurnInput(const FInputActionValue& Value);

	void MoveInput(const FInputActionValue& Value);

	void RotateTurret(FVector LookAtTarget);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void GetBall(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	bool IsAlive = true;

	FTimerHandle BounceTimerHandle;

	FTimerHandle BoostSpeedTimerHandle;

	FTimerHandle ShieldTimerHandle;
	
	void SetNewBullet(TSubclassOf<ABullet> NewBullet);

	void HandleDestruction();

	void BoostSpeedStart();

	void BoostSpeedEnd();

	void ShieldStart();

	void ShieldEnd();

	void BounceUpStart();
	
	void BounceUpEnd();

public:
	// 在蓝图里配置你的暂停界面类
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UPauseWidget> PauseWidgetClass;

	// 按下暂停键的处理函数
	void PauseGame();

	bool Noitem = true;

	bool Flawless = true;

	bool Speedrun = false;
};
