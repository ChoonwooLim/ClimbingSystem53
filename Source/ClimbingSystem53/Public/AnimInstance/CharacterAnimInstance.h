// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //�𸮾� ������ �ʼ� ��� ����
#include "Animation/AnimInstance.h" //�ִϸ��̼� �ν��Ͻ��� �����ϴ� �⺻ Ŭ���� UAnimInstance�� ����
#include "CharacterAnimInstance.generated.h" //UCLASS ��ũ�ΰ� ���Ե� Ŭ�����̹Ƿ� �ڵ� ������ ��� ������ �����ؾ� ��

class AClimbingSystem53Character;
class UCustomMovementComponent;
/**
 * 
 */
UCLASS() //�𸮾� ������ ���÷��� �ý��ۿ��� Ŭ���� �ν��� ���� ���
class CLIMBINGSYSTEM53_API UCharacterAnimInstance : public UAnimInstance 
/* CLIMBINGSYSTEM53_API �� �� Ŭ������ �ٸ� ��⿡���� ����� �� �ֵ��� ��� API�� ����
   UCharacterAnimInstance �� UAnimInstance�� ��ӹ޾� �ִϸ��̼� ������Ʈ ����� �߰��� Ŭ����*/

{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override; //�ִϸ��̼� �ν��Ͻ��� ������ �� �� �� ����Ǵ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //�� �����Ӹ��� ȣ��Ǿ� �ִϸ��̼� ���¸� ������Ʈ�ϴ� �Լ�

private:
	UPROPERTY() //GC(Garbage Collection) �ý��ۿ��� �޸� ������ �ڵ����� ����
	AClimbingSystem53Character* ClimbingSystem53Character; //�ִϸ��̼��� ����� ĳ���͸� �����ϴ� ������

	UPROPERTY()
	UCustomMovementComponent* CustomMovementComponent; //ĳ������ Ŀ���� �̵� ������ ����ϴ� ������Ʈ�� ������

	//�� �κ��� GroundSpeed ������ �𸮾� ������ ���÷��� �ý��ۿ� ����Ͽ� �������Ʈ���� ������ �� �ֵ��� �����ϴ� �ڵ��Դϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =Reference, meta = (AllowPrivateAccess = "true"))
	/*VisibleAnywhere �� �����Ϳ��� ������ ���� ���� �� ������ ������ �� ���� (��, Details �гο��� Ȯ���� �� ������ ������ �Ұ���)
       BlueprintReadOnly �� �������Ʈ���� �� ������ ���� �� ������, ������ ���� ����.(BlueprintReadWrite������ �������Ʈ���� ������ ����)
       Category = Reference �� �������Ʈ ������ ī�װ� �̸��� "Reference"�� ����. (��, �������Ʈ���� ������ �� "Reference" ī�װ� �Ʒ� ǥ�õ�)
       meta = (AllowPrivateAccess = "true") �� C++������ private ����� �������Ʈ���� ���� �����ϵ��� ���. */
	
	//GroundSpeed ����
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



