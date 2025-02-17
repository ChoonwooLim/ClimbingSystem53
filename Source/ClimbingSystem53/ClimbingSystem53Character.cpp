// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClimbingSystem53Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CustomMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "DebugHelper.h"



//////////////////////////////////////////////////////////////////////////
// AClimbingSystem53Character

AClimbingSystem53Character::AClimbingSystem53Character(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
//------------------------------------------------------------------------------
	PrimaryActorTick.bCanEverTick = true;

	bIsFlying = false;  // 기본적으로 비행 상태가 아님
	FlyingSpeed = 1200.0f; // 비행 속도 설정

	//속도 변화 로직 추가
	CurrentFlySpeed = 0.0f;
	FlyAcceleration = 500.0f; // 점진적 가속도
//-------------------------------------------------------------------------------
	
	CustomMovementComponent = Cast<UCustomMovementComponent>(GetCharacterMovement());


	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AClimbingSystem53Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


}

//////////////////////////////////////////////////////////////////////////
// Input

void AClimbingSystem53Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//--------------------------------------------------------------
	/*캐릭터가 특정 키(예: F)를 누르면 비행 모드로 진입하고, 다시 누르면 걷기로 전환되도록 만들자.*/

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 비행 모드 전환 (H 키)
	PlayerInputComponent->BindAction("ToggleFly", IE_Pressed, this, &AClimbingSystem53Character::StartFlying);

	// 비행 방향 조작
	PlayerInputComponent->BindAxis("MoveForward", this, &AClimbingSystem53Character::FlyMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AClimbingSystem53Character::FlyMoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &AClimbingSystem53Character::FlyUpDown);
	
	
	
	//------------------------------------------------------------------
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AClimbingSystem53Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AClimbingSystem53Character::Look);

		//Climbing
		EnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Started, this, &AClimbingSystem53Character::OnClimbActionStarted);
	
		//Swimming
		EnhancedInputComponent->BindAction(SwimAction, ETriggerEvent::Started, this, &AClimbingSystem53Character::OnSwimAction);

		//Flying
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Started, this, &AClimbingSystem53Character::OnFlyAction);

	}
	
}

void AClimbingSystem53Character::Move(const FInputActionValue& Value)
{
	if (!CustomMovementComponent) return;

	if(CustomMovementComponent->IsClimbing())
	{
		HandleClimbMovementInput(Value);
	}
	else
	{
		HandleGroundMovementInput(Value);
	}
	
	// input is a Vector2D
	
}

/*이 함수는 지상 이동 입력을 처리하는 기능을 수행합니다.
  즉, 플레이어의 입력(방향키 또는 조이스틱 방향값)을 받아 이동 벡터를 계산하고, 이를 적용하는 역할을 합니다.*/
void AClimbingSystem53Character::HandleGroundMovementInput(const FInputActionValue& Value)
{
	if (!Controller) return; // 컨트롤러가 있는지 확인
	/*플레이어 캐릭터는 Controller를 통해 조작됩니다.
      Controller가 없는 경우(예: AI 또는 초기화되지 않은 상태)에는 이동을 처리하지 않도록 방어 코드가 포함되어 있습니다.*/

	const FVector2D MovementVector = Value.Get<FVector2D>(); //입력 값 처리
	/*입력 값(Value)을 FVector2D로 변환하여 MovementVector 변수에 저장합니다.
       FVector2D는 2D 벡터 (X, Y)로, 일반적으로 X는 좌우 이동, Y는 앞뒤 이동을 의미합니다.
     💡 결과: MovementVector.X → 좌우 이동 입력 값
                  MovementVector.Y → 앞뒤 이동 입력 값*/

	// 현재 컨트롤러의 카메라 회전값을 가져와 Yaw만 사용
	const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

	// 전방 및 우측 벡터 계산 (간단한 방법 사용)
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); //현재 카메라 방향을 기준으로 전방(X축) 이동 벡터를 가져옵니다.
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 현재 카메라 방향을 기준으로 우측(Y축) 이동 벡터를 가져옵니다.

	// 이동 입력 적용
	AddMovementInput(ForwardDirection, MovementVector.Y); //Y 입력 값(MovementVector.Y)을 ForwardDirection에 곱해 전진/후진 이동을 수행합니다.
	AddMovementInput(RightDirection, MovementVector.X); //X 입력 값(MovementVector.X)을 RightDirection에 곱해 좌우 이동을 수행합니다.
	/*AddMovementInput()는 Unreal Engine의 CharacterMovementComponent를 통해 캐릭터의 이동을 처리합니다.
     💡 결과: W/S 또는 Up/Down 키 → 카메라 기준 앞뒤 이동
                  A/D 또는 Left/Right 키 → 카메라 기준 좌우 이동*/

}

/*이 함수는 벽을 타고 이동할 때 입력을 처리하는 기능을 수행합니다.
즉, 캐릭터가 벽을 탈 때 이동 방향을 결정하고, 이동 입력을 적용하는 역할을 합니다.*/
void AClimbingSystem53Character::HandleClimbMovementInput(const FInputActionValue& Value)
{
	if (!CustomMovementComponent) return; // 안전 체크 추가

	const FVector2D MovementVector = Value.Get<FVector2D>();

	// 벽 표면을 따라 위/아래 이동 방향 계산
	const FVector ForwardDirection = FVector::CrossProduct(
		-CustomMovementComponent->GetClimbableSurfaceNormal(),
		GetActorRightVector()
	).GetSafeNormal(); // 정규화하여 크기를 1로 맞춤

	// 벽 표면을 따라 좌우 이동 방향 계산
	const FVector RightDirection = FVector::CrossProduct(
		GetActorForwardVector(),
		-CustomMovementComponent->GetClimbableSurfaceNormal()
	).GetSafeNormal();

	// 이동 입력 적용
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AClimbingSystem53Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AClimbingSystem53Character::OnClimbActionStarted(const FInputActionValue& Value)
{
	if (!CustomMovementComponent) return;

	if (!CustomMovementComponent->IsClimbing())
	{
		CustomMovementComponent->ToggleClimbing(true);
	}
	else
	{
		CustomMovementComponent->ToggleClimbing(false);
	}
}




void AClimbingSystem53Character::OnSwimAction(const FInputActionValue& Value)
{
	//Debug::Print(TEXT("Swim action started"));

	if (!CustomMovementComponent) return;

	if (!CustomMovementComponent->IsSwimming())
	{
		CustomMovementComponent->ToggleSwimming(true);
	}
	else
	{
		CustomMovementComponent->ToggleSwimming(false);
	}
}

//-------------------------------------------------------
/*캐릭터가 특정 키(예: H)를 누르면 비행 모드로 진입하고, 다시 누르면 걷기로 전환되도록 만들자.*/

void AClimbingSystem53Character::StartFlying()
{
	bIsFlying = !bIsFlying; // 비행 모드 전환

	if (bIsFlying)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		UE_LOG(LogTemp, Warning, TEXT("Flying Mode Activated!"));
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		UE_LOG(LogTemp, Warning, TEXT("Flying Mode Deactivated!"));
	}
}

void AClimbingSystem53Character::StopFlying()
{
	if (!bIsFlying) return;

	// 비행 모드 비활성화
	bIsFlying = false;

	// 이동 모드를 걷기로 변경
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	// 현재 속도 초기화
	GetCharacterMovement()->Velocity = FVector::ZeroVector;

	UE_LOG(LogTemp, Warning, TEXT("Flying Mode Deactivated!"));
}

/*비행 모드에서는 캐릭터가 슈퍼맨처럼 전후좌우 및 상하로 이동해야 해.
이를 위해 Tick() 함수에서 매 프레임마다 캐릭터의 이동을 계산하도록 만들자.*/

void AClimbingSystem53Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFlying)
	{
		// 중력 무시
		GetCharacterMovement()->Velocity.Z = 0.0f;

		// 기울어지는 효과 추가
		FRotator NewRotation = GetActorRotation();
		NewRotation.Pitch = FMath::FInterpTo(NewRotation.Pitch, -GetVelocity().Z * 0.1f, DeltaTime, 2.0f);
		SetActorRotation(NewRotation);
	}
}

void AClimbingSystem53Character::FlyMoveForward(float Value)
{
	if (!bIsFlying || FMath::IsNearlyZero(Value)) return;

	// 속도 증가
	CurrentFlySpeed = FMath::FInterpTo(CurrentFlySpeed, FlyingSpeed, GetWorld()->GetDeltaSeconds(), FlyAcceleration);

	FVector ForwardDir = GetActorForwardVector();
	AddMovementInput(ForwardDir, Value * FlyingSpeed);
}

void AClimbingSystem53Character::FlyMoveRight(float Value)
{
	if (!bIsFlying || FMath::IsNearlyZero(Value)) return;

	// 속도 증가
	CurrentFlySpeed = FMath::FInterpTo(CurrentFlySpeed, FlyingSpeed, GetWorld()->GetDeltaSeconds(), FlyAcceleration);

	FVector RightDir = GetActorRightVector();
	AddMovementInput(RightDir, Value * FlyingSpeed);
}

void AClimbingSystem53Character::FlyUpDown(float Value)
{
	if (!bIsFlying) return;

	FVector UpDir = FVector::UpVector;
	AddMovementInput(UpDir, Value * FlyingSpeed);
}

void AClimbingSystem53Character::OnFlyAction(const FInputActionValue& Value)
{
	if (!bIsFlying)
	{
		StartFlying();
	}
	else
	{
		StopFlying();
	}

}
//---------------------------------------------------------------
/*  void AClimbingSystem53Character::OnFlyAction(const FInputActionValue& Value)
{
	//Debug::Print(TEXT("Fly action started"));

	if (!CustomMovementComponent) return;

	if (!CustomMovementComponent->IsFlying())
	{
		CustomMovementComponent->ToggleFlying(true);
	}
	else
	{
		CustomMovementComponent->ToggleFlying(false);   
	}
}
*/
