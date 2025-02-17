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
	void TraceSwimableSurfaces();// ���� ���� �����̽� Ž��
	bool IsInWater() const; // ĳ���Ͱ� �� �ӿ� �ִ��� Ȯ��
	void EnterSwimmingMode(); // ���� ��� ��ȯ


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

	bool IsWaterSurface(const FHitResult& HitResult) const; // ���� ������ �����̽����� üũ
	bool CanStartSwimming();

#pragma endregion

#pragma region FlyCore

	bool CanStartFlying();

#pragma endregion

#pragma region ClimbCoreVariables

	TArray<FHitResult> ClimbableSurfacesTrasedResults; //Ŭ���̹� ������ ǥ����� �浹 ������ ����.

	FVector CurrentClimbableSurfaceLocation; //���� Ŭ���̹� ���� ǥ���� ��ġ(�浹����)�� ����.

	FVector CurrentClimbableSurfaceNomal; //���� Ŭ���̹� ���� ǥ���� ���� ���͸� ����.

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
	bool IsClimbing() const; // ��� ������ �������� ����
	FORCEINLINE FVector GetClimbableSurfaceNormal() const { return CurrentClimbableSurfaceNomal; }

	void ToggleSwimming(bool bEnableClimb);
	bool IsSwimming() const;

	void ToggleFlying(bool bEnableClimb);
	bool IsFlying() const;

	/*��ó�� const�� ���̸�:
       ��� ������ �������� �ʴ´ٴ� ���� �����Ͽ�, �Ǽ��� ������ �� �ִ�.
       const ��ü������ ȣ�� ���������� �� �����ϰ� ����� �� �ִ�.
      ��, �б� ���� ����� �����ϴ� ��� �Լ��� const�� ���̴� ���� �Ϲ����� ��Ģ�Դϴ�.*/
	

};
