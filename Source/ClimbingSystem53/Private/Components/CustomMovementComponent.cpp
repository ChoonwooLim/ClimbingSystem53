// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ClimbingSystem53/ClimbingSystem53Character.h"


void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    TraceClimbableSurfaces();
    TraceFromEyeHeight(100.f);
}

#pragma region ClimbTraces

/* This function performs a multi-object capsule trace to detect climbable surfaces, such as walls or ledges, in Unreal Engine. 
    It uses UKismetSystemLibrary::CapsuleTraceMultiForObjects, 
    a high-level function that traces a capsule along a path and returns all objects that intersect with it. */

TArray<FHitResult> UCustomMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape)
{
  
    TArray<FHitResult> OutCapsuleTraceHitResults;

    UKismetSystemLibrary::CapsuleTraceMultiForObjects(
        this, // World context (usually 'this' pointer)
        Start, // Start position of the trace
        End, // End position of the trace
        ClimbCapsuleTraceRadius, // Capsule radius
        ClimbCapsuleTraceHalfHeight, // Capsule half-height
        ClimableSurfaceTraceTypes, // Object types to detect
        false, // Trace complex? (false = simple collision)
        TArray<AActor*>(), // Actors to ignore
        bShowDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None, // Debug visualization
        OutCapsuleTraceHitResults, // Output: Array of FHitResults
        false // Ignore self
        );

    return OutCapsuleTraceHitResults; // Returns all hit objects
}

FHitResult UCustomMovementComponent::DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool bShowDebugShape)
{
    FHitResult OutHit;

    if (!GetWorld()) return OutHit;

    UKismetSystemLibrary::LineTraceSingleForObjects(
        GetWorld(), // World context 
        Start, // Start position of the trace
        End, // End position of the trace
        ClimableSurfaceTraceTypes, // Object types to detect
        false, // Trace complex? (false = simple collision)
        TArray<AActor*>(), // Actors to ignore
        bShowDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None, // Debug visualization
        OutHit, // Output: Array of FHitResults
        false // Ignore self
    );

    return OutHit;
}

#pragma endregion

#pragma region ClimbCore

/*This function performs a capsule trace to detect climbable surfaces directly in front of the player.
It calls DoCapsuleTraceMultiByObject() to find walls, ledges, or other climbable objects.*/

void UCustomMovementComponent::TraceClimbableSurfaces()
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

    DoCapsuleTraceMultiByObject(Start, End, true);
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

void UCustomMovementComponent::TraceFromEyeHeight(float TraceDistance, float TraceStartOffset)
{
    const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
    const FVector EyeHeightOffset = UpdatedComponent->GetUpVector() * (CharacterOwner->BaseEyeHeight + TraceStartOffset);
    const FVector Start = ComponentLocation + EyeHeightOffset;
    const FVector End = Start + UpdatedComponent->GetForwardVector() * TraceDistance;

    DoLineTraceSingleByObject(Start, End, true);
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