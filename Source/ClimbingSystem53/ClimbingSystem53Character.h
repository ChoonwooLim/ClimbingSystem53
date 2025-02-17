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

/* Ŭ���� ���� (AClimbingSystem53Character)
    ACharacter Ŭ������ ������� �� ĳ���� Ŭ����.
    ī�޶�, �Է�(Input), Ŀ���� �̵� ������Ʈ(Custom Movement Component) ���� ����.
    ��� ����� ����.
    UE5�� Enhanced Input System�� ����Ͽ� �Է� ó��.*/

UCLASS(config=Game)
class AClimbingSystem53Character : public ACharacter
{
	
	GENERATED_BODY()

public:
	AClimbingSystem53Character(const FObjectInitializer& ObjectInitializer); //������ (Constructor)
	/*�� �����ڴ� ��ü �ʱ�ȭ(Object Initialization)�� ����մϴ�.
       FObjectInitializer�� ����Ͽ� �θ� Ŭ������ �ʱ�ȭ ������ ������ �� �ֽ��ϴ�.
      �� �κ��� .cpp ���Ͽ��� ���� �ʱ�ȭ �ڵ尡 �ۼ��� ���Դϴ�.*/

private:
    // ī�޶� ���� ����
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom; /*ĳ���� ���ʿ� ī�޶� ��ġ�ϴ� ������ ��(Spring Arm).
                                                             ī�޶��� ��ġ�� �����ϰ� �浹�� �����ϴ� ����� ���.*/

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera; /*������ ȭ�鿡 ǥ�õǴ� ���� ī�޶�(Follow Camera).
                                                           CameraBoom�� �����Ǿ� ������, ĳ���Ͱ� �̵��ϸ� �̸� ���� ������.*/


	//�̵� �ý��� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UCustomMovementComponent* CustomMovementComponent; /*�⺻ CharacterMovementComponent�� Ȯ���� ����� ���� �̵� ������Ʈ.
                                                                         ���, ����, ���� ���� Ư�� �̵� ����� �����ϱ� ���� ������ ������Ʈ�� ����ϴ� ����.*/
	
	
																		 
	//�Է�(Input) �ý��� ���� ����																	 
	 /** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext; /*UE5�� Enhanced Input System�� ����Ͽ� �Է��� �����ϴ� ����.
                                                                    ���� ���, "WASD" Ű, ��Ʈ�ѷ� ���̽�ƽ, ��ġ �Է� ���� �ϳ��� �Է� �������� ó�� ����.*/

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction; /*����(Jump) �Է��� ó���ϴ� UInputAction ��ü.
                                            �÷��̾ �����̽��� �Ǵ� ��Ʈ�ѷ� ��ư�� ������ �� ���� �̺�Ʈ�� �߻�.*/

	
	// �̵� ���� �Է� ó�� �Լ�								
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);/*�⺻ �̵� �Լ���, �Է� ��(Value)�� �޾� �̵� ó��.
                                                                    ĳ���Ͱ� ���� �̵� ������ �������� Ȯ���� ��, ������ �Լ��� ȣ��.*/

	void HandleGroundMovementInput(const FInputActionValue& Value); /*���󿡼� �̵��� �� ȣ��Ǵ� �Լ�.
                                                                                                       �⺻���� �ȱ�, �ٱ� ���� �̵��� ó��.*/
	void HandleClimbMovementInput(const FInputActionValue& Value); /*ĳ���Ͱ� ���� ���� ��(Climbing) ȣ��Ǵ� �Լ�.
                                                                                     ���� ���� �����̸� ĳ���Ͱ� ���� Ÿ�� �̵��� �� �ֵ��� ������ ��.*/

	//ī�޶� ȸ��(Look) �Է� ó��
/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction; //���콺 ������ �Ǵ� ��Ʈ�ѷ��� ������ ��ƽ(Right Stick) �Է��� ó��.

	/** Called for looking input */
	void Look(const FInputActionValue& Value); //ī�޶� ȸ���� ó���ϴ� �Լ�.

	//Ư�� �̵�(���, ����, ����) ���� �Է� ó��	
	/** Climb Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ClimbAction; //���(Climbing) ����� Ȱ��ȭ�ϴ� �Է�.

	/** Called for Climbing input */
	void OnClimbActionStarted(const FInputActionValue& Value); /*�÷��̾ ��� ��ư�� ������ ȣ��Ǵ� �Լ�.
                                                                                     ���� ���� �� �ִ� �������� Ȯ�� ��, �̵� ����� ����.*/



protected:
	//�Է� ���ε� �� �ʱ�ȭ
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;/*�Է� ���ε��� �����ϴ� �Լ�.
                                                                                         Move, Look, OnClimbActionStarted ���� �Լ��� UE�� �Է� �ý��۰� �����.*/

	
	// To add mapping context
	virtual void BeginPlay() override; /*������ ���۵� �� ����Ǵ� �Լ�.
                                                     �Է� ���� ���ؽ�Ʈ�� ����� ���ɼ��� ŭ.*/


public:

	//���� �Լ� (Getter �Լ�)-> FORCEINLINE�� ����Ͽ� ���� ����ȭ / ���� ī�޶� ��, ī�޶�, Ŀ���� �̵� ������Ʈ�� ��ȯ.
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UCustomMovementComponent* GetCustomMovementComponent() const { return CustomMovementComponent; }

};

