// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomMovementComponent.generated.h"

//Ŀ���� �̵� ��� ���� (ECustomMovementMode)
UENUM(BlueprintType) // BlueprintType�� ����Ͽ� �������Ʈ������ ��� �����ϵ��� ����.
namespace ECustomMovementMode //Ŀ���� �̵� ���(���)�� ����.
{
	enum Type
	{
		MOVE_Climb UMETA(DisplayName = "Climb Mode") //�������Ʈ���� ǥ�õ� �̸� ����.
	};
}


/** Ŭ���� ���� (UCustomMovementComponent)*/
UCLASS()
class CLIMBINGSYSTEM53_API UCustomMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	//UCharacterMovementComponent�� ����Ͽ� �⺻ �̵� ������Ʈ�� Ȯ��.

protected:

	//�������̵�� �ֿ� �Լ�
#pragma region Overriden Functions

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//�� ������ ����Ǵ� �̵� ���� ������Ʈ�� ó��.

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	/*�̵� ���(���, ����, ���� ��)�� ����� �� ȣ���.
       �̵� ��� ���� �� �ʿ��� �ʱ�ȭ �Ǵ� ���� �۾� ����.*/

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	// **����� ���� �̵� ���(���)**������ ���� ������ ó��.

	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;
	//���� �̵� ��忡 ���� �ִ� �ӵ��� ���ӵ��� ��ȯ.

#pragma endregion

	
private:

#pragma region ClimbTraces
	//�浹(Ʈ���̽�) ���� �Լ� : �� �Լ����� ��� ������ ǥ���� ã�� �� ����.

	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false,bool bDrawPersistantShapes = false);
	//ĸ�� Ʈ���̽��� ����Ͽ� ���� ���� �浹�� ����.

	FHitResult DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false, bool bDrawPersistantShapes = false);
	//���� Ʈ���̽��� ����Ͽ� ���� �浹�� ����.

#pragma endregion

//���(Climbing) ���� ���
#pragma region ClimbCore

	//��� ���� ���� Ȯ�� �Լ�
	bool TraceClimbableSurfaces(); //ĳ���Ͱ� ����� �� �ִ� ǥ���� ã�� (���� Ʈ���̽� �Ǵ� ĸ�� Ʈ���̽��� Ȱ��).

	FHitResult TraceFromEyeHeight(float TraceDistance, float TraceStartOffset = 0.f); //ĳ������ �ü� ���̿��� ���� �����Ͽ� ����� �������� Ȯ��.

	bool CanStartClimbing(); //���� ���¿��� ����� ������ �� �ִ��� ���θ� �Ǵ�.

	//��� ��� ��ȯ
	void StartClimbing();//��� ���� ��ȯ�ϰ�, �̵� �ý����� ����.

	void StopClimbing(); //��� ��带 �����ϰ�, �⺻ �̵� ���·� ����.

	
	//��� ���� ���� ó��
	void PhysClimb(float deltaTime, int32 Iterations); //��� ���� �� �������� �̵��� ó��.

	void ProcessClimbableSurfaceInfo(); //���� ��� ���� ǥ���� �浹 ������ �м�.

	bool CheckShouldStopClimbing(); //�� �̻� ����� �� ���� ��Ȳ���� �Ǵ�.

	FQuat GetClimbRotation(float DeltaTime); //���� ���� �̵��� �� ĳ������ ȸ�� ���� ���.

	void SnapMovementToClimbableSurfaces(float DeltaTime); //��� ���� ǥ�鿡 ĳ������ �̵��� �ε巴�� ����.


#pragma endregion

	//��� ���� ����
#pragma region ClimbCoreVariables

	TArray<FHitResult> ClimbableSurfacesTrasedResults; //Ŭ���̹� ������ ǥ����� �浹 ������ ����.

	FVector CurrentClimbableSurfaceLocation; //���� Ŭ���̹� ���� ǥ���� ��ġ(�浹����)�� ����.

	FVector CurrentClimbableSurfaceNomal; //���� Ŭ���̹� ���� ǥ���� ���� ���͸� ����.

#pragma endregion

//�������Ʈ���� ���� ������ ����
#pragma region ClimbBPVariables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery> > ClimableSurfaceTraceTypes; //����� ������ **ǥ���� ����(Object Type)**�� ����.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceRadius = 50.F; //��� ������ ���� ĸ�� Ʈ���̽� ũ�� ����.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceHalfHeight = 72.0f; //��� ������ ���� ĸ�� Ʈ���̽� ũ�� ����.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxBreakClimbDeceleration = 400.f; //��� �� ���� �� ���� �ӵ�.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxClimbSpeed = 100.f; //��� �� �ִ� �ӵ�(100.f).

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxClimbAcceleration = 300.f; //��� �� �ִ� ���ӵ�(300.f).

#pragma endregion

public:
	void ToggleClimbing(bool bEnableClimb); //��� ��带 Ȱ��ȭ �Ǵ� ��Ȱ��ȭ.
	bool IsClimbing() const; // ���� ��� ������ Ȯ��-��� ������ �������� ����
	FORCEINLINE FVector GetClimbableSurfaceNormal() const { return CurrentClimbableSurfaceNomal; } //���� ��� ���� ǥ���� ���� ���͸� ��ȯ.

	/*��ó�� const�� ���̸�:
       ��� ������ �������� �ʴ´ٴ� ���� �����Ͽ�, �Ǽ��� ������ �� �ִ�.
       const ��ü������ ȣ�� ���������� �� �����ϰ� ����� �� �ִ�.
      ��, �б� ���� ����� �����ϴ� ��� �Լ��� const�� ���̴� ���� �Ϲ����� ��Ģ�Դϴ�.*/
	

};
