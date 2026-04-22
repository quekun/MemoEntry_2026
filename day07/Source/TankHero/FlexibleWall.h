

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlexibleWall.generated.h"

UCLASS()
class TANKHERO_API AFlexibleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlexibleWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsLower = false;

	// 计时器结束后的处理函数
	void AttemptToRaise();

	// 执行真正的上升逻辑
	void RaiseWall();

	void LowerWall();

	UPROPERTY(EditAnywhere)
	float CheckRadius = 50.0f; // 检测盒的高度/范围

	UPROPERTY(EditAnywhere)
	float WallLowerDuration = 3.0f; 
	
	FTimerHandle RaiseTimerHandle;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WallMesh;

	UPROPERTY(EditAnywhere)
	class UMover* Mover;
};
