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
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
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
	//Debug::Print(TEXT("Climb action started"));

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
/*캐릭터가 특정 키(예: F)를 누르면 비행 모드로 진입하고, 다시 누르면 걷기로 전환되도록 만들자.*/

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
