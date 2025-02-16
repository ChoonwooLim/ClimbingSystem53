// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ClimbingSystem53/ClimbingSystem53Character.h"
#include "ClimbingSystem53/DebugHelper.h"


void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    /*TraceClimbableSurfaces();
    TraceFromEyeHeight(100.f);*/
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
        }
        else
        {
            Debug::Print(TEXT("Can NOT start climbing"));
        }
    }
    else
    {
        // Stop climbing
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

}

void UCustomMovementComponent::StopClimbing()
{
    SetMovementMode(MOVE_Custom, ECustomMovementMode::MOVE_Climb);
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


