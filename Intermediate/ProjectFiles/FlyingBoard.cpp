#include "FlyingBoard.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"

AFlyingBoard::AFlyingBoard()
{
    PrimaryActorTick.bCanEverTick = true;

    // ���� ������ ���� ����
    BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
    RootComponent = BoardMesh;

    // �����ϴ� �̵��� ���� Movement Component �߰�
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

// ����/���� �̵�
void AFlyingBoard::MoveForward(float Value)
{
    if (MovementComponent)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

// �¿� �̵�
void AFlyingBoard::MoveRight(float Value)
{
    if (MovementComponent)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

// ���� �̵� (�� ����)
void AFlyingBoard::MoveUp(float Value)
{
    if (MovementComponent)
    {
        AddMovementInput(GetActorUpVector(), Value);
    }
}
