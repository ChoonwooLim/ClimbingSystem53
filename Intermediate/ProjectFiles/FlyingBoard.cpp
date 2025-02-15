#include "FlyingBoard.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"

AFlyingBoard::AFlyingBoard()
{
    PrimaryActorTick.bCanEverTick = true;

    // 비행 보드의 외형 설정
    BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
    RootComponent = BoardMesh;

    // 부유하는 이동을 위한 Movement Component 추가
    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void AFlyingBoard::BeginPlay()
{
    Super::BeginPlay();
}

void AFlyingBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 전진/후진 이동
void AFlyingBoard::MoveForward(float Value)
{
    if (MovementComponent)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

// 좌우 이동
void AFlyingBoard::MoveRight(float Value)
{
    if (MovementComponent)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

// 상하 이동 (고도 조절)
void AFlyingBoard::MoveUp(float Value)
{
    if (MovementComponent)
    {
        AddMovementInput(GetActorUpVector(), Value);
    }
}
