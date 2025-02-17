// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ClimbingSystem53/ClimbingSystem53Character.h"
#include "Components/CapsuleComponent.h"

#include "ClimbingSystem53/DebugHelper.h"


void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    /*TraceClimbableSurfaces();
    TraceFromEyeHeight(100.f);*/
}

void UCustomMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
    if(IsClimbing()) // 벽 타기 모드 진입 시
    { 
    bOrientRotationToMovement = false;
    CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(48.f);
    }

    else if (PreviousMovementMode == MOVE_Custom && PreviousCustomMode == ECustomMovementMode::MOVE_Climb)// 벽 타기에서 벗어날 때
    {
        bOrientRotationToMovement = true; 
        CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(96.f);

        // 캐릭터 회전 초기화 (Yaw 유지)
        const FRotator NewRotation(0.f, UpdatedComponent->GetComponentRotation().Yaw, 0.f);
        
        UpdatedComponent->SetRelativeRotation(NewRotation);

        // 즉시 정지
        StopMovementImmediately();
    }

    // 부모 클래스의 기본 이동 모드 변경 로직 수행
    Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

}

void UCustomMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
    if (IsClimbing())
    {
        PhysClimb(deltaTime, Iterations);
    }

    Super::PhysCustom(deltaTime, Iterations);
}

float UCustomMovementComponent::GetMaxSpeed() const
{
    if (IsClimbing())
    {
        return MaxClimbSpeed;
    }
    else
    {
        return Super::GetMaxSpeed();
    }
}

float UCustomMovementComponent::GetMaxAcceleration() const
{
    if (IsClimbing())
    {
        return MaxClimbAcceleration;
    }
    else
    {
        return Super::GetMaxAcceleration();
    }
}


#pragma region ClimbTraces

/* This function performs a multi-object capsule trace to detect climbable surfaces, such as walls or ledges, in Unreal Engine. 
    It uses UKismetSystemLibrary::CapsuleTraceMultiForObjects, 
    a high-level function that traces a capsule along a path and returns all objects that intersect with it. */

TArray<FHitResult> UCustomMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape, bool bDrawPersistantShapes)
{
  
    TArray<FHitResult> OutCapsuleTraceHitResults;

    EDrawDebugTrace::Type DebugTraceType = EDrawDebugTrace::None;

    if (bShowDebugShape)
    {
        DebugTraceType = EDrawDebugTrace::ForOneFrame;

        if (bDrawPersistantShapes)
        {
            DebugTraceType = EDrawDebugTrace::Persistent;
        }
    }

    UKismetSystemLibrary::CapsuleTraceMultiForObjects(
        this, // World context (usually 'this' pointer)
        Start, // Start position of the trace
        End, // End position of the trace
        ClimbCapsuleTraceRadius, // Capsule radius
        ClimbCapsuleTraceHalfHeight, // Capsule half-height
        ClimableSurfaceTraceTypes, // Object types to detect
        false, // Trace complex? (false = simple collision)
        TArray<AActor*>(), // Actors to ignore
        DebugTraceType, // Debug visualization
        OutCapsuleTraceHitResults, // Output: Array of FHitResults
        false // Ignore self
        );

    return OutCapsuleTraceHitResults; // Returns all hit objects
}

FHitResult UCustomMovementComponent::DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool bShowDebugShape, bool bDrawPersistantShapes)
{
    FHitResult OutHit;



    if (!GetWorld()) return OutHit;

    EDrawDebugTrace::Type DebugTraceType = EDrawDebugTrace::None;

    if (bShowDebugShape)
    {
        DebugTraceType = EDrawDebugTrace::ForOneFrame;

        if (bDrawPersistantShapes)
        {
            DebugTraceType = EDrawDebugTrace::Persistent;
        }
    }

    UKismetSystemLibrary::LineTraceSingleForObjects(
        GetWorld(), // World context 
        Start, // Start position of the trace
        End, // End position of the trace
        ClimableSurfaceTraceTypes, // Object types to detect
        false, // Trace complex? (false = simple collision)
        TArray<AActor*>(), // Actors to ignore
        DebugTraceType, // Debug visualization
        OutHit, // Output: Array of FHitResults
        false // Ignore self
    );

    return OutHit;
}

#pragma endregion

#pragma region Swim State

void UCustomMovementComponent::TraceSwimableSurfaces()
{
    if (!CharacterOwner) return;

    FVector Start = CharacterOwner->GetActorLocation();
    FVector End = Start - FVector(0, 0, 200.0f); // 아래로 200 유닛 체크

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);

    // 바닥 트레이스 실행
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, QueryParams);

    if (bHit && HitResult.bBlockingHit)
    {
        // 감지된 서페이스가 수영 가능한지 확인
        if (IsWaterSurface(HitResult))
        {
            EnterSwimmingMode();
        }
    }
}

bool UCustomMovementComponent::IsWaterSurface(const FHitResult& HitResult) const
{
    if (!HitResult.GetActor()) return false;

    // 예제: 특정 물 머티리얼이 적용된 서페이스인지 확인
    UPrimitiveComponent* HitComponent = HitResult.GetComponent();
    if (HitComponent && HitComponent->GetMaterial(0))
    {
        FString MaterialName = HitComponent->GetMaterial(0)->GetName();
        return MaterialName.Contains(TEXT("Water"));
    }

    return false;
}

void UCustomMovementComponent::EnterSwimmingMode()
{
    if (MovementMode != MOVE_Swimming)
    {
        SetMovementMode(MOVE_Swimming);
        UE_LOG(LogTemp, Log, TEXT("Entered Swimming Mode"));
    }
}

bool UCustomMovementComponent::IsInWater() const
{
    FVector Location = CharacterOwner->GetActorLocation();
    FVector WaterTestLocation = Location + FVector(0, 0, -50.0f); // 50 유닛 아래 확인

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Location, WaterTestLocation, ECC_WorldStatic, QueryParams);

    return bHit && IsWaterSurface(HitResult);
}

/*설명
 TraceSwimableSurfaces()
캐릭터 위치 아래로 라인 트레이스 수행하여 서페이스 체크
감지된 경우 IsWaterSurface() 함수를 호출하여 수영 가능한 서페이스인지 확인
수영 가능하면 EnterSwimmingMode() 호출하여 수영 모드로 전환

IsWaterSurface()
감지된 서페이스의 머티리얼 이름이 "Water"을 포함하면 물이라고 간주
필요하면 커스텀 태그나 물 볼륨을 감지하는 방식으로 변경 가능
EnterSwimmingMode()

현재 이동 모드가 MOVE_Swimming이 아니라면 수영 모드로 변경
SetMovementMode(MOVE_Swimming); 호출

IsInWater()
캐릭터 위치에서 아래로 라인 트레이스를 수행하여 물에 있는지 확인
게임플레이 중 계속 물이 있는지 체크하는 데 사용*/

#pragma endregion

void UCustomMovementComponent::ToggleClimbing(bool bEnableClimb)
{
    if (bEnableClimb)
    {
        if (CanStartClimbing())
        {
            // Enter the climb stase
            Debug::Print(TEXT("Can start climbing"));
            StartClimbing();
        }
        else
        {
            Debug::Print(TEXT("Can NOT start climbing"));
        }
    }
    else
    {
        StopClimbing();
    }
}

void UCustomMovementComponent::ToggleSwimming(bool bEnableSwim)
{
    if (bEnableSwim)
    {
        if (CanStartSwimming())
        {
            SetMovementMode(MOVE_Custom, ECustomMovementMode::MOVE_Swim);
            Debug::Print(TEXT("Entered Swimming Mode"));
        }
        else
        {
            Debug::Print(TEXT("Cannot enter Swimming Mode"));
        }
    }
    else
    {
        SetMovementMode(MOVE_Walking);
        Debug::Print(TEXT("Exited Swimming Mode"));
    }
}

void UCustomMovementComponent::ToggleFlying(bool bEnableFly)
{
    if (bEnableFly)
    {
        if (CanStartFlying())
        {
            SetMovementMode(MOVE_Custom, ECustomMovementMode::MOVE_Fly);
            Debug::Print(TEXT("Entered Flying Mode"));
        }
        else
        {
            Debug::Print(TEXT("Cannot enter Flying Mode"));
        }
    }
    else
    {
        SetMovementMode(MOVE_Walking);
        Debug::Print(TEXT("Exited Flying Mode"));
    }

}


bool UCustomMovementComponent::CanStartClimbing()
{
    if(IsFalling()) return false;
    if (!TraceClimbableSurfaces()) return false;
    if (!TraceFromEyeHeight(100.f).bBlockingHit) return false;

    return true;
}

void UCustomMovementComponent::StartClimbing()
{
    SetMovementMode(MOVE_Custom, ECustomMovementMode::MOVE_Climb);
}

void UCustomMovementComponent::StopClimbing()
{
    SetMovementMode(MOVE_Falling);
}

void UCustomMovementComponent::PhysClimb(float deltaTime, int32 Iterations) //Unreal Engine에서 캐릭터의 클라이밍(벽 오르기) 기능을 구현하는 핵심 이동 로직
{
    if (!UpdatedComponent) //UpdatedComponent가 nullptr인지 확인
    {
        // UpdatedComponent가 nullptr이면 충돌할 가능성이 있으므로 체크 필요.
        return;
    }

            if (deltaTime < MIN_TICK_TIME) //deltaTime이 너무 작으면 함수 종료
        {
            return;
            //MIN_TICK_TIME보다 작은 경우 너무 짧은 시간(=무시할 수 있을 정도로 작은 시간)이므로 아예 이동 계산을 하지 않고 리턴.
        }
            /*Process all the climbable surface info*/
        TraceClimbableSurfaces();
        ProcessClimbableSurfaceInfo();

            /*Check if we should climbing*/

        RestorePreAdditiveRootMotionVelocity(); //루트 모션 속도 복원
        /* 루트 모션을 사용하는 애니메이션(Root Motion)이 있는 경우, 속도를 복원.
           클라이밍 애니메이션에 의해 속도가 변하는 경우, 이를 다시 적용할 준비를 함.*/

        if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity()) //클라이밍 속도 계산 : 루트 모션(AnimRootMotion)이나 OverrideVelocity가 적용되지 않은 경우에만 속도를 계산.
        {
            // Define the max climb speed and acceleration
            CalcVelocity(deltaTime, 0.f, true, MaxBreakClimbDeceleration); //CalcVelocity()를 호출하여 클라이밍 최대 속도 및 감속
            /*CalcVelocity() 함수 역할
              - 속도를 업데이트하는 Unreal Engine 기본 함수 (PhysWalking() 등에서도 사용).
              - MaxBreakClimbDeceleration: 클라이밍 중 감속량을 나타냄.*/
        }

        ApplyRootMotionToVelocity(deltaTime); //루트 모션 적용 : 루트 모션(애니메이션 속도)이 있을 경우 현재 속도(Velocity)에 반영

        FVector OldLocation = UpdatedComponent->GetComponentLocation(); //UpdatedComponent의 현재 월드 좌표를 저장
        const FVector Adjusted = Velocity * deltaTime; //현재 속도(Velocity)를 이용하여 이번 프레임에서 이동할 거리(변위) 계산.
        FHitResult Hit(1.f); // 충돌 정보를 저장할 구조체 초기화 (Hit.Time = 1.f은 충돌 없음 상태).

        // Handle climb rotation
        SafeMoveUpdatedComponent(Adjusted, GetClimbRotation(deltaTime), true, Hit); //벽을 따라 이동 수행
        /*SafeMoveUpdatedComponent()
           Adjusted(이동 거리)만큼 이동을 시도.
           충돌 발생 시 Hit에 충돌 정보 저장.
           true: 충돌 시 자동으로 처리 (Sweep 방식).*/
        /*충돌(Hit)이 발생하는 경우
          벽이 너무 가파르거나 장애물이 있으면 Hit.Time < 1.f가 됨.*/

        if (Hit.Time < 1.f) //이동 중 충돌이 발생한 경우.
        {
            //adjust and try again
            HandleImpact(Hit, deltaTime, Adjusted); //충돌한 표면이 오를 수 있는지 확인하고, 충돌 반응을 처리하는 함수.
            FVector ClimbDir = Velocity.GetSafeNormal();//Hit.Normal이 아닌 ClimbDir을 사용하여 벽을 타고 자연스럽게 이동.
            SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true); //벽을 타고 이동할 수 있도록 표면을 따라 미끄러지도록 보정.  
            /*SlideAlongSurface() 역할
              충돌 후, 벽을 따라 자연스럽게 미끄러지도록 이동 보정.
              예: 캐릭터가 완전히 멈추지 않고 벽을 따라 옆으로 이동할 수 있도록 함.*/
        }

        if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity()) //최종 속도 업데이트:애니메이션 루트 모션이 없을 경우, 최종 속도 재계산.
        {
            Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
            /*실제 이동한 거리 / deltaTime을 이용해 새로운 속도를 계산.
              이 과정은 클라이밍 중 속도를 자연스럽게 업데이트하는 데 사용됨.*/
        }

        /*Snap movement to climbable surfaces*/
        SnapMovementToClimbableSurfaces(deltaTime);

}

void UCustomMovementComponent::ProcessClimbableSurfaceInfo() //감지된 클라이밍 가능한 표면들에 대한 정보를 처리하여 평균적인 위치와 방향(법선 벡터)을 계산
{
    // 여러 개의 충돌 데이터를 합산할 것이므로 초기값을 ZeroVector로 설정.
    CurrentClimbableSurfaceLocation = FVector::ZeroVector; //현재 클라이밍 표면의 위치를 초기화 → (0,0,0).
    CurrentClimbableSurfaceNomal = FVector::ZeroVector; //현재 클라이밍 표면의 Nomal을 초기화 → (0,0,0).

    if (ClimbableSurfacesTrasedResults.IsEmpty()) return; //클라이밍 가능한 표면이 없으면 함수 종료
    int32 SurfaceCount = ClimbableSurfacesTrasedResults.Num();

    //감지된 모든 클라이밍 표면의 정보를 합산 : 여러 개의 충돌 데이터가 있을 경우, 평균적인 위치와 방향을 구하기 위해 값들을 더함.
    /*for 루프를 사용하여 모든 감지된 충돌(FHitResult)을 순회.
      각 충돌의 충돌 위치(ImpactPoint)를 합산 → CurrentClimbableSurfaceLocation에 누적.
      각 충돌의 법선(ImpactNormal)을 합산 → CurrentClimbableSurfaceNomal에 누적.*/
    for (const FHitResult& TracedHitResult : ClimbableSurfacesTrasedResults)
    {
        CurrentClimbableSurfaceLocation += TracedHitResult.ImpactPoint;
        CurrentClimbableSurfaceNomal += TracedHitResult.ImpactNormal;
    }

    //이렇게 하면 벡터의 길이가 너무 작아서 정규화가 불가능한 경우 안전하게 처리됨.
    CurrentClimbableSurfaceLocation /= SurfaceCount;

    if (!CurrentClimbableSurfaceNomal.IsNearlyZero()) //법선 벡터(CurrentClimbableSurfaceNomal)가 0에 가까울 경우 정규화를 피함.
    {
        CurrentClimbableSurfaceNomal = CurrentClimbableSurfaceNomal.GetSafeNormal();
    }

    //평균 위치 계산
    CurrentClimbableSurfaceLocation /= ClimbableSurfacesTrasedResults.Num();
    /*감지된 표면 개수(ClimbableSurfacesTrasedResults.Num())로 CurrentClimbableSurfaceLocation을 나누어 평균 위치를 계산.
      📌 이렇게 하면 클라이밍 가능한 여러 개의 표면이 감지되었을 때, 그 중간 위치를 중심으로 이동할 수 있음.*/

    //평균 Nomal 벡터 정규화
    CurrentClimbableSurfaceNomal = CurrentClimbableSurfaceNomal.GetSafeNormal();
    /*평균 법선 벡터를 정규화하여 길이를 1.0으로 조정.
      GetSafeNormal() 함수는 벡터의 길이를 1로 조정하며, 만약 벡터의 길이가 0에 가까우면 안전하게 처리.
     📌 이렇게 하면 벽 방향을 정확하게 정할 수 있으며, 이동 방향 보정에 사용할 수 있음.*/

}


/*함수 개요
  목적: 현재 UpdatedComponent의 회전을 가져오고, 목표 회전(TargetQuat)을 계산한 후, 일정한 속도로 현재 회전에서 목표 회전으로 보간(lerp)하는 역할을 합니다.
  주요 역할: 벽을 타고 오를 때, 캐릭터의 방향을 벽의 표면 방향에 맞추기 위해 사용됩니다.
*/
FQuat UCustomMovementComponent::GetClimbRotation(float DeltaTime)
{
    const FQuat CurrentQuat = UpdatedComponent->GetComponentQuat(); //현재 회전 가져오기
    /*현재 UpdatedComponent(캐릭터의 충돌 캡슐 또는 메쉬)의 회전(FQuat)을 가져옵니다.
      이 값을 기반으로 현재 회전 상태를 유지하거나, 새로운 목표 회전 값으로 보간할 수 있습니다.*/

    if (HasAnimRootMotion() || CurrentRootMotion.HasOverrideVelocity()) //루트 모션 또는 외부 힘이 적용된 경우 현재 회전 유지
    {
        return CurrentQuat;
    }
    /*루트 모션(HasAnimRootMotion())이 적용된 경우
      애니메이션이 직접 캐릭터의 움직임을 제어하는 상태이므로 별도로 회전을 변경하지 않습니다.
      현재 루트 모션에 강제 속도 오버라이드(HasOverrideVelocity())가 적용된 경우
      특정한 외부 움직임(예: 시네마틱, 강제 이동)이 있는 경우도 회전을 변경하지 않습니다.
       결론: 이 두 조건이 만족되면 현재 회전(CurrentQuat)을 그대로 반환하여 변경하지 않습니다.*/

    const FQuat TargetQuat = FRotationMatrix::MakeFromX(-CurrentClimbableSurfaceNomal).ToQuat(); //목표 회전값 설정
    /*FRotationMatrix::MakeFromX(Vector).ToQuat()을 사용하여 새로운 방향을 기반으로 회전(FQuat)을 생성합니다.
       CurrentClimbableSurfaceNomal는 현재 플레이어가 오르고 있는 벽의 법선 벡터입니다.
       -CurrentClimbableSurfaceNomal를 사용한 이유:
       법선 벡터는 벽의 수직 방향을 나타내지만, 캐릭터는 벽을 바라보도록 해야 하므로 음수(-)를 취해 방향을 반전시킵니다.
       즉, 벽의 법선 방향과 반대 방향으로 캐릭터가 향하도록 회전 값을 설정하는 것입니다. */

    return FMath::QInterpTo(CurrentQuat, TargetQuat, DeltaTime, 5.f); //보간하여 최종 회전값 반환
     /*FMath::QInterpTo를 사용하여 현재 회전에서 목표 회전으로 보간(lerp)합니다.
       DeltaTime을 사용하여 프레임 독립적인 보간을 수행합니다.
        5.f는 보간 속도를 의미합니다. 값이 클수록 빠르게 목표 회전값으로 이동합니다.*/
}

/*이 함수는 캐릭터를 현재 오르고 있는 벽(Climbable Surface)에 맞춰 부드럽게 정렬하는 역할을 합니다. 
  즉, 캐릭터가 벽에서 너무 멀어지거나 잘못된 위치로 움직이지 않도록 조정하는 역할을 합니다.*/
void UCustomMovementComponent::SnapMovementToClimbableSurfaces(float DeltaTime)
{
    //캐릭터의 현재 방향 및 위치 가져오기
    const FVector ComponentForward = UpdatedComponent->GetForwardVector(); //(캐릭터)의 정면 방향 벡터 (ForwardVector)를 가져옵니다.
    const FVector ComponentLocation = UpdatedComponent->GetComponentLocation(); //UpdatedComponent의 현재 월드 위치를 가져옵니다.

    //벽과의 거리(투영) 계산
    const FVector ProjectedCharacterToSurface =
        (CurrentClimbableSurfaceLocation - ComponentLocation).ProjectOnTo(ComponentForward);
    /*CurrentClimbableSurfaceLocation → 현재 캐릭터가 오르는 벽의 위치.
      (CurrentClimbableSurfaceLocation - ComponentLocation) → 캐릭터에서 벽까지의 벡터.
       ProjectOnTo(ComponentForward) → 이 벡터를 캐릭터의 ForwardVector에 투영하여, 캐릭터의 정면 방향으로 벽까지 얼마나 떨어져 있는지 계산.
    💡 결과: ProjectedCharacterToSurface는 캐릭터의 정면 방향 기준으로 벽까지의 거리입니다.
                이 값이 크다면, 캐릭터가 벽에서 떨어져 있다는 뜻이며, 작다면 벽에 가까운 상태입니다.*/

    //벽을 향한 이동 벡터 계산
    const FVector SnapVector = -CurrentClimbableSurfaceNomal * ProjectedCharacterToSurface.Length();
    /*CurrentClimbableSurfaceNomal: 현재 벽의 법선 벡터 (벽이 바라보는 방향).
       ProjectedCharacterToSurface.Length(): 벽과 캐릭터 사이의 거리 (정면 방향 기준).
     💡 결과: SnapVector는 벽의 법선 방향(-CurrentClimbableSurfaceNomal)을 따라 벽까지의 거리만큼 이동하도록 설정된 벡터입니다.
                  즉, 캐릭터가 벽에서 너무 멀리 떨어졌다면, 다시 벽 쪽으로 붙도록 이동하는 힘을 제공합니다.*/

   //캐릭터를 벽 쪽으로 이동
    UpdatedComponent->MoveComponent(
        SnapVector * DeltaTime * MaxClimbSpeed,
        UpdatedComponent->GetComponentQuat(),
        true);
    /*MoveComponent()를 사용하여 SnapVector 방향으로 캐릭터를 움직입니다.
      이동 속도는 MaxClimbSpeed를 곱하여 조절되며, DeltaTime을 곱해 프레임 독립적인 이동을 보장합니다.
      현재 회전(UpdatedComponent->GetComponentQuat())은 유지하면서 이동합니다.
      마지막 인수 true는 Sweep을 활성화하여 충돌을 감지할 수 있도록 합니다.
     💡 결과: 캐릭터가 벽과의 거리(SnapVector)만큼 부드럽게 이동하며, 벽에서 떨어지지 않고 계속 밀착된 상태를 유지합니다.

*/
}

bool UCustomMovementComponent::CanStartSwimming()
{
    return IsInWater(); // 물 속에 있는지 확인하여 수영 가능 여부 반환
}

bool UCustomMovementComponent::CanStartFlying()
{
    return IsFalling(); // 공중에 있을 때만 비행 가능하도록 설정
}


bool UCustomMovementComponent::IsClimbing() const
{
    return MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::MOVE_Climb;
}

bool UCustomMovementComponent::IsSwimming() const
{
    return MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::MOVE_Swim;
}

bool UCustomMovementComponent::IsFlying() const
{
    return MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::MOVE_Fly;
}


#pragma region ClimbCore

/*This function performs a capsule trace to detect climbable surfaces directly in front of the player.
It calls DoCapsuleTraceMultiByObject() to find walls, ledges, or other climbable objects.*/



//Trace for climbable surfaces, return true if there are indeed valid surface, false otherwise.
bool UCustomMovementComponent::TraceClimbableSurfaces()
{
    const FVector StartOffset = UpdatedComponent->GetForwardVector() * 30.f; 
    /*Gets the forward direction of the character (GetForwardVector()).
       Moves the starting point of the trace 30 units forward.
       Why? This ensures the trace starts slightly in front of the character (instead of inside them) to avoid self-detection*/

    const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
    /*Gets the character’s current position (GetComponentLocation()).
       Adds StartOffset to move the trace forward (away from the player).*/

    const FVector End = Start + UpdatedComponent->GetForwardVector();
    /*Moves the End position slightly forward from Start.
       This defines the trace direction.
       End Position = Start Position + 1 Unit Forward.*/

    ClimbableSurfacesTrasedResults = DoCapsuleTraceMultiByObject(Start,End,true);

    return !ClimbableSurfacesTrasedResults.IsEmpty();
    /*Calls DoCapsuleTraceMultiByObject(), which performs the actual capsule trace.
       Parameters:
       Start → Start position of the trace.
       End → End position of the trace.
       true → Enables debug visualization.*/

    /*Summary
         Traces forward to detect climbable walls.
         Uses capsule trace for accurate collision detection.
         Avoids self-detection by offsetting the start position.
         Supports debugging with bShowDebugShape.
         Can be optimized by increasing trace distance.*/
}


FHitResult UCustomMovementComponent::TraceFromEyeHeight(float TraceDistance, float TraceStartOffset)
{
    if (!CharacterOwner) return FHitResult();
    
    const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
    const FVector EyeHeightOffset = UpdatedComponent->GetUpVector() * (CharacterOwner->BaseEyeHeight + TraceStartOffset);
    const FVector Start = ComponentLocation + EyeHeightOffset;
    const FVector End = Start + UpdatedComponent->GetForwardVector() * TraceDistance;

     return DoLineTraceSingleByObject(Start, End);
}
/*이 함수는 캐릭터의 눈 높이(Eye Height)에서 특정 거리(TraceDistance)까지 라인 트레이스를 수행하는 기능을 합니다.
   즉, 캐릭터의 정면을 따라 특정 거리만큼 라인 트레이스를 발사하여 충돌 여부를 감지할 수 있습니다.*/

   /*📌 정리: 함수 동작 과정
      캐릭터의 위치(ComponentLocation)를 가져옴
      눈 높이를 계산(EyeHeightOffset)하여 트레이스 시작 위치(Start) 설정
      캐릭터가 바라보는 방향(ForwardVector)으로 TraceDistance만큼 나아간 End 위치 설정
      DoLineTraceSingleByObject()를 호출하여 라인 트레이스를 실행
      트레이스 결과를 통해 충돌 검사 가능
      
      🚀 최종 요약
       캐릭터의 눈 높이에서 정면으로 TraceDistance만큼 라인 트레이스를 발사하는 함수
       트레이스 결과를 통해 벽, 장애물, 목표물 감지 가능
       bShowDebugShape = true이면 디버그 시각화를 통해 트레이스 확인 가능

       이제 이 함수는 플레이어의 시야를 기반으로 충돌 감지, 계단 탐지, 벽 감지 등에 활용할 수 있습니다!
      */

#pragma endregion


