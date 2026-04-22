// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

class UInputAction;
class UInputMappingContext;

#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


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

	FVector MeshInternalOrigin;

	FVector CurrentRecoilOffset;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RecoilStrength = 50.f; // 后坐力强度

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RecoilRestoreSpeed = 15.f; // 复位速度

	FVector	DefaultLoc ;
	FRotator DefaultRot ;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	APlayerController* PlayerController;

	virtual void Fire();

	void TurnInput(const FInputActionValue& Value);

	void MoveInput(const FInputActionValue& Value);

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
	
	void SetNewBullet(TSubclassOf<ABullet> NewBullet);

	void HandleDestruction();

	void SetPlayerEnabled(bool Enabled);
	
};
