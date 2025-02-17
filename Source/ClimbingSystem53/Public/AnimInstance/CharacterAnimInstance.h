// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //언리얼 엔진의 필수 헤더 파일
#include "Animation/AnimInstance.h" //애니메이션 인스턴스를 관리하는 기본 클래스 UAnimInstance를 포함
#include "CharacterAnimInstance.generated.h" //UCLASS 매크로가 포함된 클래스이므로 자동 생성된 헤더 파일을 포함해야 함

class AClimbingSystem53Character;
class UCustomMovementComponent;
/**
 * 
 */
UCLASS() //언리얼 엔진의 리플렉션 시스템에서 클래스 인식을 위해 사용
class CLIMBINGSYSTEM53_API UCharacterAnimInstance : public UAnimInstance 
/* CLIMBINGSYSTEM53_API → 이 클래스를 다른 모듈에서도 사용할 수 있도록 모듈 API를 노출
   UCharacterAnimInstance → UAnimInstance를 상속받아 애니메이션 업데이트 기능을 추가한 클래스*/

{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override; //애니메이션 인스턴스가 생성될 때 한 번 실행되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //매 프레임마다 호출되어 애니메이션 상태를 업데이트하는 함수

private:
	UPROPERTY() //GC(Garbage Collection) 시스템에서 메모리 관리를 자동으로 해줌
	AClimbingSystem53Character* ClimbingSystem53Character; //애니메이션이 적용될 캐릭터를 저장하는 포인터

	UPROPERTY()
	UCustomMovementComponent* CustomMovementComponent; //캐릭터의 커스텀 이동 로직을 담당하는 컴포넌트의 포인터

	//이 부분은 GroundSpeed 변수를 언리얼 엔진의 리플렉션 시스템에 등록하여 블루프린트에서 접근할 수 있도록 설정하는 코드입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =Reference, meta = (AllowPrivateAccess = "true"))
	/*VisibleAnywhere → 에디터에서 변수의 값을 읽을 수 있지만 수정할 수 없음 (즉, Details 패널에서 확인할 수 있지만 변경은 불가능)
       BlueprintReadOnly → 블루프린트에서 이 변수를 읽을 수 있지만, 수정할 수는 없음.(BlueprintReadWrite였으면 블루프린트에서 수정도 가능)
       Category = Reference → 블루프린트 변수의 카테고리 이름을 "Reference"로 설정. (즉, 블루프린트에서 정리될 때 "Reference" 카테고리 아래 표시됨)
       meta = (AllowPrivateAccess = "true") → C++에서는 private 멤버라도 블루프린트에서 접근 가능하도록 허용. */
	
	//GroundSpeed 변수
	float GroundSpeed;
	void GetGroundSpeed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	float AirSpeed;
	void GetAirSpeed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;
	void GetShouldMove();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;
	void GetIsFalling();

};



