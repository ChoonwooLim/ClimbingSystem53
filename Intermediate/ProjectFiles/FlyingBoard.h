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

    // 비행 보드 이동 관련 함수
    void MoveForward(float Value);
    void MoveRight(float Value);
    void MoveUp(float Value);

private:
    // 비행 보드의 시각적 표현
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BoardMesh;

    // 비행 보드의 이동을 관리하는 컴포넌트
    UPROPERTY(VisibleAnywhere)
    UFloatingPawnMovement* MovementComponent;
};
