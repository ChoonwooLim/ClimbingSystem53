// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomMovementComponent.generated.h"

//커스텀 이동 모드 정의 (ECustomMovementMode)
UENUM(BlueprintType) // BlueprintType을 사용하여 블루프린트에서도 사용 가능하도록 지정.
namespace ECustomMovementMode //커스텀 이동 모드(등반)를 정의.
{
	enum Type
	{
		MOVE_Climb UMETA(DisplayName = "Climb Mode") //블루프린트에서 표시될 이름 설정.
	};
}


/** 클래스 정의 (UCustomMovementComponent)*/
UCLASS()
class CLIMBINGSYSTEM53_API UCustomMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	//UCharacterMovementComponent를 상속하여 기본 이동 컴포넌트를 확장.

protected:

	//오버라이드된 주요 함수
#pragma region Overriden Functions

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//매 프레임 실행되는 이동 관련 업데이트를 처리.

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	/*이동 모드(등반, 수영, 비행 등)가 변경될 때 호출됨.
       이동 모드 변경 시 필요한 초기화 또는 정리 작업 수행.*/

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	// **사용자 정의 이동 모드(등반)**에서의 물리 연산을 처리.

	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;
	//현재 이동 모드에 따라 최대 속도와 가속도를 반환.

#pragma endregion

	
private:

#pragma region ClimbTraces
	//충돌(트레이스) 관련 함수 : 이 함수들은 등반 가능한 표면을 찾을 때 사용됨.

	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false,bool bDrawPersistantShapes = false);
	//캡슐 트레이스를 사용하여 여러 개의 충돌을 감지.

	FHitResult DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false, bool bDrawPersistantShapes = false);
	//라인 트레이스를 사용하여 단일 충돌을 감지.

#pragma endregion

//등반(Climbing) 관련 기능
#pragma region ClimbCore

	//등반 가능 여부 확인 함수
	bool TraceClimbableSurfaces(); //캐릭터가 등반할 수 있는 표면을 찾음 (라인 트레이스 또는 캡슐 트레이스를 활용).

	FHitResult TraceFromEyeHeight(float TraceDistance, float TraceStartOffset = 0.f); //캐릭터의 시선 높이에서 벽을 감지하여 등반이 가능한지 확인.

	bool CanStartClimbing(); //현재 상태에서 등반을 시작할 수 있는지 여부를 판단.

	//등반 모드 전환
	void StartClimbing();//등반 모드로 전환하고, 이동 시스템을 조정.

	void StopClimbing(); //등반 모드를 해제하고, 기본 이동 상태로 복귀.

	
	//등반 물리 연산 처리
	void PhysClimb(float deltaTime, int32 Iterations); //등반 중일 때 물리적인 이동을 처리.

	void ProcessClimbableSurfaceInfo(); //현재 등반 중인 표면의 충돌 정보를 분석.

	bool CheckShouldStopClimbing(); //더 이상 등반할 수 없는 상황인지 판단.

	FQuat GetClimbRotation(float DeltaTime); //벽을 따라 이동할 때 캐릭터의 회전 값을 계산.

	void SnapMovementToClimbableSurfaces(float DeltaTime); //등반 중인 표면에 캐릭터의 이동을 부드럽게 맞춤.


#pragma endregion

	//등반 관련 변수
#pragma region ClimbCoreVariables

	TArray<FHitResult> ClimbableSurfacesTrasedResults; //클라이밍 가능한 표면들의 충돌 정보를 저장.

	FVector CurrentClimbableSurfaceLocation; //현재 클라이밍 중인 표면의 위치(충돌지점)를 저장.

	FVector CurrentClimbableSurfaceNomal; //현재 클라이밍 중인 표면의 법선 벡터를 저장.

#pragma endregion

//블루프린트에서 조정 가능한 변수
#pragma region ClimbBPVariables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery> > ClimableSurfaceTraceTypes; //등반이 가능한 **표면의 유형(Object Type)**을 지정.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceRadius = 50.F; //등반 감지를 위한 캡슐 트레이스 크기 설정.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceHalfHeight = 72.0f; //등반 감지를 위한 캡슐 트레이스 크기 설정.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxBreakClimbDeceleration = 400.f; //등반 중 멈출 때 감속 속도.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxClimbSpeed = 100.f; //등반 중 최대 속도(100.f).

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement : Climbing", meta = (AllowPrivateAccess = "true"))
	float MaxClimbAcceleration = 300.f; //등반 중 최대 가속도(300.f).

#pragma endregion

public:
	void ToggleClimbing(bool bEnableClimb); //등반 모드를 활성화 또는 비활성화.
	bool IsClimbing() const; // 현재 등반 중인지 확인-멤버 변수를 변경하지 않음
	FORCEINLINE FVector GetClimbableSurfaceNormal() const { return CurrentClimbableSurfaceNomal; } //현재 등반 중인 표면의 법선 벡터를 반환.

	/*위처럼 const를 붙이면:
       멤버 변수를 변경하지 않는다는 것을 보장하여, 실수를 방지할 수 있다.
       const 객체에서도 호출 가능해져서 더 유연하게 사용할 수 있다.
      즉, 읽기 전용 기능을 제공하는 멤버 함수는 const를 붙이는 것이 일반적인 규칙입니다.*/
	

};
