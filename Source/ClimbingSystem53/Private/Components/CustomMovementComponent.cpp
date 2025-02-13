// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    TraceClimbableSurfaces();
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

#pragma endregion