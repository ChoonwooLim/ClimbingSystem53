#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyingBoard.generated.h"

class UStaticMeshComponent;
class UFloatingPawnMovement;

UCLASS()
class AClimbingSystemCharacter : public APawn
{
    GENERATED_BODY()

public:
    AFlyingBoard();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // ���� ���� �̵� ���� �Լ�
    void MoveForward(float Value);
    void MoveRight(float Value);
    void MoveUp(float Value);

private:
    // ���� ������ �ð��� ǥ��
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BoardMesh;

    // ���� ������ �̵��� �����ϴ� ������Ʈ
    UPROPERTY(VisibleAnywhere)
    UFloatingPawnMovement* MovementComponent;
};
