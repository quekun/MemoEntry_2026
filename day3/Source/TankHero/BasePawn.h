

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Kismet/GameplayStatics.h"

#include "Bullet.h"
#include "NiagaraFunctionlibrary.h"


#include "BasePawn.generated.h"

UCLASS()
class TANKHERO_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChassisMesh;

	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HatchMesh;

	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* wheelsMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* BulletSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> BulletClass;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* DeathParticles;

	UPROPERTY(EditAnywhere)
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate = 1.f; 

	bool bIsFiringCoolDown = false; //  «∑Ò’˝‘⁄¿‰»¥

	FTimerHandle FireTimerHandle;   //

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire();

	void ResetFireCoolDown();

	void HandleDestruction();

};
