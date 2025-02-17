// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/CharacterAnimInstance.h" //UCharacterAnimInstance 클래스의 헤더 파일
#include "ClimbingSystem53/ClimbingSystem53Character.h" //캐릭터 클래스
#include "Components/CustomMovementComponent.h" //커스텀 이동 컴포넌트
#include "Kismet/KismetMathLibrary.h" //언리얼 엔진의 수학 관련 유틸리티 함수가 포함된 라이브러리


//NativeInitializeAnimation() - 애니메이션 초기화
void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation(); //부모 클래스(UAnimInstance)의 초기화 함수를 먼저 실행하여 기본적인 초기화를 수행.

	ClimbingSystem53Character = Cast<AClimbingSystem53Character>(TryGetPawnOwner());
	/*TryGetPawnOwner() : 현재 애니메이션 인스턴스를 소유한 Pawn을 반환.
       즉, 이 애니메이션 블루프린트가 어느 캐릭터에 적용되는지 확인하는 역할.
       Cast<AClimbingSystem53Character>(...) : Pawn이 AClimbingSystem53Character 타입인지 확인하고, 맞다면 포인터로 변환하여 저장.
	   결과적으로: NativeInitializeAnimation()은 이 애니메이션 블루프린트가 적용된 캐릭터와 해당 캐릭터의 이동 컴포넌트를 찾아 저장하는 역할을 함.
	   */

	if (ClimbingSystem53Character)
	{
		CustomMovementComponent = ClimbingSystem53Character->GetCustomMovementComponent();
	}
}

//NativeUpdateAnimation(float DeltaSeconds) - 애니메이션 업데이트
void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds); //부모 클래스(UAnimInstance)의 업데이트 함수를 호출하여 기본 동작을 유지.

	if (!ClimbingSystem53Character || !CustomMovementComponent) return;

	GetGroundSpeed(); //지상 이동 속도 계산
	GetAirSpeed(); //공중 속도 계산
	GetShouldMove(); //이동 여부 확인
	GetIsFalling(); //공중 상태 여부 확인

}

//GetGroundSpeed() - 지상 이동 속도 계산
void UCharacterAnimInstance::GetGroundSpeed()
{
	GroundSpeed = UKismetMathLibrary::VSizeXY(ClimbingSystem53Character->GetVelocity());
	/*GetVelocity()로 현재 속도를 가져온 후, XY 축(지면 속도)만 계산.
      즉, 캐릭터가 X, Y 방향으로 얼마나 빠르게 움직이는지 측정.
      Z(수직 속도)는 무시함 → 점프나 낙하의 영향을 받지 않고 수평 이동 속도만 측정.
	  결론: GroundSpeed 값은 캐릭터가 걷거나 뛰는 속도를 결정하는 데 사용될 가능성이 높음.*/
}

//GetAirSpeed() - 공중 속도 계산
void UCharacterAnimInstance::GetAirSpeed()
{
	AirSpeed = ClimbingSystem53Character->GetVelocity().Z;
	//캐릭터의 Z 축(수직 방향) 속도를 가져옴. 즉, 점프하거나 떨어질 때의 속도를 저장.
	//결론: AirSpeed 값은 캐릭터의 점프 또는 낙하 속도를 결정하는 데 사용될 가능성이 있음.
}

//GetShouldMove() - 이동 여부 확인
void UCharacterAnimInstance::GetShouldMove()
{
	bShouldMove =
		CustomMovementComponent->GetCurrentAcceleration().Size() > 0 &&
		GroundSpeed > 5.f &&
		!bIsFalling;
	/*bShouldMove는 캐릭터가 이동 중인지 여부를 판단하는 변수.
      캐릭터가 이동 중이라고 판단하는 조건
       CustomMovementComponent->GetCurrentAcceleration().Size() > 0
       현재 가속도가 0보다 크면 캐릭터가 실제로 이동하려고 함.
       GroundSpeed > 5.f
       이동 속도가 5 이상이면 걷거나 뛰고 있는 상태.
       !bIsFalling
        캐릭터가 공중에 떠 있지 않아야 함 (즉, 지면에 있어야 함).
		결론: bShouldMove 값은 캐릭터가 걷기/뛰기 애니메이션을 실행할지 결정하는 데 사용됨. */
}

//GetIsFalling() - 공중 상태 여부 확인
void UCharacterAnimInstance::GetIsFalling()
{
	bIsFalling = CustomMovementComponent->IsFalling();
	/*CustomMovementComponent->IsFalling()
       캐릭터가 공중에 떠 있으면 true, 지면에 있으면 false를 반환.
       점프, 낙하 등 공중 상태를 감지하는 함수.
	   결론: bIsFalling 값은 캐릭터가 점프 또는 낙하 상태일 때 애니메이션을 변경하는 데 사용됨.*/
}

