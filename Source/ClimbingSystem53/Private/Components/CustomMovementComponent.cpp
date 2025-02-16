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
    if(IsClimbing())
    { 
    bOrientRotationToMovement = false;
    CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(48.f);
    }

    if (PreviousMovementMode == MOVE_Custom && PreviousCustomMode == ECustomMovementMode::MOVE_Climb)
    {
        bOrientRotationToMovement = true; 
        CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(96.f);

        StopMovementImmediately();
    }

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
        SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit); //벽을 따라 이동 수행
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

    ClimbableSurfacesTrasedResults = DoCapsuleTraceMultiByObject(Start,End,true,true);

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

     return DoLineTraceSingleByObject(Start, End, true, true);
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


