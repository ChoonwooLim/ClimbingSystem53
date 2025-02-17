// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ClimbingSystem53Character.generated.h"

class UCustomMovementComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/* 클래스 개요 (AClimbingSystem53Character)
    ACharacter 클래스를 기반으로 한 캐릭터 클래스.
    카메라, 입력(Input), 커스텀 이동 컴포넌트(Custom Movement Component) 등을 포함.
    등반 기능을 지원.
    UE5의 Enhanced Input System을 사용하여 입력 처리.*/

UCLASS(config=Game)
class AClimbingSystem53Character : public ACharacter
{
	
	GENERATED_BODY()

public:
	AClimbingSystem53Character(const FObjectInitializer& ObjectInitializer); //생성자 (Constructor)
	/*이 생성자는 객체 초기화(Object Initialization)를 담당합니다.
       FObjectInitializer를 사용하여 부모 클래스의 초기화 과정을 제어할 수 있습니다.
      이 부분은 .cpp 파일에서 실제 초기화 코드가 작성될 것입니다.*/

private:
    // 카메라 관련 변수
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom; /*캐릭터 뒤쪽에 카메라를 배치하는 스프링 암(Spring Arm).
                                                             카메라의 위치를 조절하고 충돌을 방지하는 기능을 담당.*/

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera; /*실제로 화면에 표시되는 추적 카메라(Follow Camera).
                                                           CameraBoom에 부착되어 있으며, 캐릭터가 이동하면 이를 따라 움직임.*/


	//이동 시스템 관련 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UCustomMovementComponent* CustomMovementComponent; /*기본 CharacterMovementComponent를 확장한 사용자 정의 이동 컴포넌트.
                                                                         등반, 수영, 비행 같은 특수 이동 기능을 지원하기 위해 별도의 컴포넌트를 사용하는 구조.*/
	
	
																		 
	//입력(Input) 시스템 관련 변수																	 
	 /** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext; /*UE5의 Enhanced Input System을 사용하여 입력을 매핑하는 역할.
                                                                    예를 들어, "WASD" 키, 컨트롤러 조이스틱, 터치 입력 등을 하나의 입력 맵핑으로 처리 가능.*/

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction; /*점프(Jump) 입력을 처리하는 UInputAction 객체.
                                            플레이어가 스페이스바 또는 컨트롤러 버튼을 눌렀을 때 점프 이벤트를 발생.*/

	
	// 이동 관련 입력 처리 함수								
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);/*기본 이동 함수로, 입력 값(Value)을 받아 이동 처리.
                                                                    캐릭터가 현재 이동 가능한 상태인지 확인한 후, 적절한 함수를 호출.*/

	void HandleGroundMovementInput(const FInputActionValue& Value); /*지상에서 이동할 때 호출되는 함수.
                                                                                                       기본적인 걷기, 뛰기 등의 이동을 처리.*/
	void HandleClimbMovementInput(const FInputActionValue& Value); /*캐릭터가 벽을 오를 때(Climbing) 호출되는 함수.
                                                                                     벽을 향해 움직이면 캐릭터가 벽을 타고 이동할 수 있도록 구현될 것.*/

	//카메라 회전(Look) 입력 처리
/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction; //마우스 움직임 또는 컨트롤러의 오른쪽 스틱(Right Stick) 입력을 처리.

	/** Called for looking input */
	void Look(const FInputActionValue& Value); //카메라 회전을 처리하는 함수.

	//특수 이동(등반, 수영, 비행) 관련 입력 처리	
	/** Climb Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ClimbAction; //등반(Climbing) 기능을 활성화하는 입력.

	/** Called for Climbing input */
	void OnClimbActionStarted(const FInputActionValue& Value); /*플레이어가 등반 버튼을 누르면 호출되는 함수.
                                                                                     벽을 오를 수 있는 상태인지 확인 후, 이동 방식을 변경.*/



protected:
	//입력 바인딩 및 초기화
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;/*입력 바인딩을 설정하는 함수.
                                                                                         Move, Look, OnClimbActionStarted 등의 함수가 UE의 입력 시스템과 연결됨.*/

	
	// To add mapping context
	virtual void BeginPlay() override; /*게임이 시작될 때 실행되는 함수.
                                                     입력 매핑 컨텍스트를 등록할 가능성이 큼.*/


public:

	//보조 함수 (Getter 함수)-> FORCEINLINE을 사용하여 성능 최적화 / 각각 카메라 붐, 카메라, 커스텀 이동 컴포넌트를 반환.
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UCustomMovementComponent* GetCustomMovementComponent() const { return CustomMovementComponent; }

};

