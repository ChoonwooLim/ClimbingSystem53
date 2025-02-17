// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomMovementComponent.generated.h"


UENUM(BlueprintType)
namespace ECustomMovementMode
{
	enum Type
	{
		MOVE_Climb UMETA(DisplayName = "Climb Mode"),
		MOVE_Fly   UMETA(DisplayName = "Fly Mode"),
		MOVE_Swim   UMETA(DisplayName = "Swim Mode")
	};
}


/**
 * 
 */
UCLASS()
class CLIMBINGSYSTEM53_API UCustomMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

protected:

#pragma region Overriden Functions

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;

#pragma endregion

	
	
public:
	void TraceSwimableSurfaces();// 수영 가능 서페이스 탐색
	bool IsInWater() const; // 캐릭터가 물 속에 있는지 확인
	void EnterSwimmingMode(); // 수영 모드 전환


private:

#pragma region ClimbTraces

	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false,bool bDrawPersistantShapes = false);
	FHitResult DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false, bool bDrawPersistantShapes = false);

#pragma endregion

#pragma region ClimbCore

	bool TraceClimbableSurfaces();

	FHitResult TraceFromEyeHeight(float TraceDistance, float TraceStartOffset = 0.f);

	bool CanStartClimbing();

	void StartClimbing();

	void StopClimbing();

	void PhysClimb(float deltaTime, int32 Iterations);

	void ProcessClimbableSurfaceInfo();

	FQuat GetClimbRotation(float DeltaTime);

	void SnapMovementToClimbableSurfaces(float DeltaTime);

#pragma endregion

#pragma region SwimCore

	bool IsWaterSurface(const FHitResult& HitResult) const; // 수영 가능한 서페이스인지 체크
	bool CanStartSwimming();

#pragma endregion

#pragma region FlyCore

	bool CanStartFlying();

#pragma endregion

#pragma region ClimbCoreVariables

	TArray<FHitResult> ClimbableSurfacesTrasedResults; //클라이밍 가능한 표면들의 충돌 정보를 저장.

	FVector CurrentClimbableSurfaceLocation; //현재 클라이밍 중인 표면의 위치(충돌지점)를 저장.

	FVector CurrentClimbableSurfaceNomal; //현재 클라이밍 중인 표면의 법선 벡터를 저장.

#pragma endregion

#pragma region SwimCoreVariables

	TArray<FHitResult> SwimableSurfacesTrasedResults;

#pragma endregion

#pragma region FlyCoreVariables



#pragma endregion

#pragma region ClimbBPVariables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery> > ClimableSurfaceTraceTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceRadius = 50.F;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceHalfHeight = 72.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxBreakClimbDeceleration = 400.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxClimbSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxClimbAcceleration = 300.f;

#pragma endregion

public:
	void ToggleClimbing(bool bEnableClimb);
	bool IsClimbing() const; // 멤버 변수를 변경하지 않음
	FORCEINLINE FVector GetClimbableSurfaceNormal() const { return CurrentClimbableSurfaceNomal; }

	void ToggleSwimming(bool bEnableClimb);
	bool IsSwimming() const;

	void ToggleFlying(bool bEnableClimb);
	bool IsFlying() const;

	/*위처럼 const를 붙이면:
       멤버 변수를 변경하지 않는다는 것을 보장하여, 실수를 방지할 수 있다.
       const 객체에서도 호출 가능해져서 더 유연하게 사용할 수 있다.
      즉, 읽기 전용 기능을 제공하는 멤버 함수는 const를 붙이는 것이 일반적인 규칙입니다.*/
	

};
