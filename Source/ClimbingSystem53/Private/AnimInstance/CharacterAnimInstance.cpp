// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/CharacterAnimInstance.h" //UCharacterAnimInstance Ŭ������ ��� ����
#include "ClimbingSystem53/ClimbingSystem53Character.h" //ĳ���� Ŭ����
#include "Components/CustomMovementComponent.h" //Ŀ���� �̵� ������Ʈ
#include "Kismet/KismetMathLibrary.h" //�𸮾� ������ ���� ���� ��ƿ��Ƽ �Լ��� ���Ե� ���̺귯��


//NativeInitializeAnimation() - �ִϸ��̼� �ʱ�ȭ
void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation(); //�θ� Ŭ����(UAnimInstance)�� �ʱ�ȭ �Լ��� ���� �����Ͽ� �⺻���� �ʱ�ȭ�� ����.

	ClimbingSystem53Character = Cast<AClimbingSystem53Character>(TryGetPawnOwner());
	/*TryGetPawnOwner() : ���� �ִϸ��̼� �ν��Ͻ��� ������ Pawn�� ��ȯ.
       ��, �� �ִϸ��̼� �������Ʈ�� ��� ĳ���Ϳ� ����Ǵ��� Ȯ���ϴ� ����.
       Cast<AClimbingSystem53Character>(...) : Pawn�� AClimbingSystem53Character Ÿ������ Ȯ���ϰ�, �´ٸ� �����ͷ� ��ȯ�Ͽ� ����.
	   ���������: NativeInitializeAnimation()�� �� �ִϸ��̼� �������Ʈ�� ����� ĳ���Ϳ� �ش� ĳ������ �̵� ������Ʈ�� ã�� �����ϴ� ������ ��.
	   */

	if (ClimbingSystem53Character)
	{
		CustomMovementComponent = ClimbingSystem53Character->GetCustomMovementComponent();
	}
}

//NativeUpdateAnimation(float DeltaSeconds) - �ִϸ��̼� ������Ʈ
void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds); //�θ� Ŭ����(UAnimInstance)�� ������Ʈ �Լ��� ȣ���Ͽ� �⺻ ������ ����.

	if (!ClimbingSystem53Character || !CustomMovementComponent) return;

	GetGroundSpeed(); //���� �̵� �ӵ� ���
	GetAirSpeed(); //���� �ӵ� ���
	GetShouldMove(); //�̵� ���� Ȯ��
	GetIsFalling(); //���� ���� ���� Ȯ��

}

//GetGroundSpeed() - ���� �̵� �ӵ� ���
void UCharacterAnimInstance::GetGroundSpeed()
{
	GroundSpeed = UKismetMathLibrary::VSizeXY(ClimbingSystem53Character->GetVelocity());
	/*GetVelocity()�� ���� �ӵ��� ������ ��, XY ��(���� �ӵ�)�� ���.
      ��, ĳ���Ͱ� X, Y �������� �󸶳� ������ �����̴��� ����.
      Z(���� �ӵ�)�� ������ �� ������ ������ ������ ���� �ʰ� ���� �̵� �ӵ��� ����.
	  ���: GroundSpeed ���� ĳ���Ͱ� �Ȱų� �ٴ� �ӵ��� �����ϴ� �� ���� ���ɼ��� ����.*/
}

//GetAirSpeed() - ���� �ӵ� ���
void UCharacterAnimInstance::GetAirSpeed()
{
	AirSpeed = ClimbingSystem53Character->GetVelocity().Z;
	//ĳ������ Z ��(���� ����) �ӵ��� ������. ��, �����ϰų� ������ ���� �ӵ��� ����.
	//���: AirSpeed ���� ĳ������ ���� �Ǵ� ���� �ӵ��� �����ϴ� �� ���� ���ɼ��� ����.
}

//GetShouldMove() - �̵� ���� Ȯ��
void UCharacterAnimInstance::GetShouldMove()
{
	bShouldMove =
		CustomMovementComponent->GetCurrentAcceleration().Size() > 0 &&
		GroundSpeed > 5.f &&
		!bIsFalling;
	/*bShouldMove�� ĳ���Ͱ� �̵� ������ ���θ� �Ǵ��ϴ� ����.
      ĳ���Ͱ� �̵� ���̶�� �Ǵ��ϴ� ����
       CustomMovementComponent->GetCurrentAcceleration().Size() > 0
       ���� ���ӵ��� 0���� ũ�� ĳ���Ͱ� ������ �̵��Ϸ��� ��.
       GroundSpeed > 5.f
       �̵� �ӵ��� 5 �̻��̸� �Ȱų� �ٰ� �ִ� ����.
       !bIsFalling
        ĳ���Ͱ� ���߿� �� ���� �ʾƾ� �� (��, ���鿡 �־�� ��).
		���: bShouldMove ���� ĳ���Ͱ� �ȱ�/�ٱ� �ִϸ��̼��� �������� �����ϴ� �� ����. */
}

//GetIsFalling() - ���� ���� ���� Ȯ��
void UCharacterAnimInstance::GetIsFalling()
{
	bIsFalling = CustomMovementComponent->IsFalling();
	/*CustomMovementComponent->IsFalling()
       ĳ���Ͱ� ���߿� �� ������ true, ���鿡 ������ false�� ��ȯ.
       ����, ���� �� ���� ���¸� �����ϴ� �Լ�.
	   ���: bIsFalling ���� ĳ���Ͱ� ���� �Ǵ� ���� ������ �� �ִϸ��̼��� �����ϴ� �� ����.*/
}

