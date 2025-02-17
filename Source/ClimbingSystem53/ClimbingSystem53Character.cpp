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

//클래스 초기화 (AClimbingSystem53Character 생성자)
AClimbingSystem53Character::AClimbingSystem53Character(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomMovementComponent>(ACharacter::CharacterMovementComponentName))
/*기본 캐릭터 이동 컴포넌트를 **사용자 정의 이동 컴포넌트(UCustomMovementComponent)**로 교체.
ACharacter::CharacterMovementComponentName을 사용하여 기본 이동 컴포넌트를 교체.
Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomMovementComponent>...)을 통해 부모 클래스 초기화.*/

{
	//콜리전 캡슐 크기 설정
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f); /*CapsuleComponent는 캐릭터의 충돌 영역을 정의.
                                                                                 높이(96.0f) 및 반지름(42.0f)를 설정하여 충돌 판정을 조정.*/
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CustomMovementComponent = Cast<UCustomMovementComponent>(GetCharacterMovement());


	//기본 이동 설정
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; //캐릭터가 이동하는 방향으로 자동 회전.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // 회전 속도 설정(500도/초).

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f; //점프 높이 조절.
	GetCharacterMovement()->AirControl = 0.35f; //공중에서의 방향 전환 가능성 설정.
	GetCharacterMovement()->MaxWalkSpeed = 500.f; //최대 이동 속도 500 설정.
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	//카메라 설정
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	/*카메라 붐(SpringArmComponent) 생성
        CameraBoom->TargetArmLength = 400.0f; → 카메라와 캐릭터 사이의 거리 설정.
        bUsePawnControlRotation = true; → 플레이어가 마우스를 움직이면 카메라가 회전하도록 설정.*/

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	/*FollowCamera는 **카메라 붐(SpringArm)**에 부착됨.
       bUsePawnControlRotation = false; → 카메라는 붐의 회전에만 영향을 받도록 설정.*/

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}


//BeginPlay() - 입력 매핑 컨텍스트 추가
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
	/*게임이 시작되면 BeginPlay()가 호출됨.
       UEnhancedInputLocalPlayerSubsystem을 통해 Enhanced Input System을 활성화.
       Subsystem->AddMappingContext(DefaultMappingContext, 0); → 기본 입력 매핑 컨텍스트 추가.*/

}

//////////////////////////////////////////////////////////////////////////
// Input

void AClimbingSystem53Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
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
	
	}
	
}


//기본 이동 (Move(), HandleGroundMovementInput())
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
	// 현재 캐릭터가 등반 중인지 확인한 후, 적절한 이동 함수를 호출.
	
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
		-CustomMovementComponent->GetClimbableSurfaceNormal(), // 벽의 법선
		- GetActorUpVector() // 캐릭터의 위쪽 방향
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

