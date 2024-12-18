// Fill out your copyright notice in the Description page of Project Settings.


#include "PerformActionBase.h"
#include "PerceptionSubsystem.h"
#include "DrawDebugHelpers.h"
#include "PerceptionComponent.h"

#define SHAPE_DIMENSIONS(...) __VA_ARGS__
#define MULTITRACE_SHAPE_BYPROFILE(InHitResults,InActor,InProfileName,InCollisionShape,\
									InShapeDimensions,InCollisionParams)\
GetWorld()->SweepMultiByProfile(\
	InHitResults, InActor->GetActorLocation(),InActor->GetActorLocation(),\
	FQuat::Identity,InProfileName,\
	InCollisionShape(InShapeDimensions),InCollisionParams);

#define DRAW_DEBUG(InDrawType,InActor,InShapeDimensions,InColor,InTickInterval) \
InDrawType(GetWorld(), InActor->GetActorLocation(),InShapeDimensions,InColor,false,InTickInterval);

void ActorDetected(const TArray<FHitResult>& InHitResults,const AActor* InActor);


void UPerformActionBase::DoAction(AActor* InActor, const FPerceptionInfo& InPerceptionInfo)
{
	
}

void UPerformActionSphere::DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo)
{
	if (!InActor) return;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(InActor);
	TArray<FHitResult> HitResults;
	
	DRAW_DEBUG(DrawDebugSphere,InActor,SHAPE_DIMENSIONS(InPerceptionInfo.Radius, InPerceptionInfo.Segments),
	FColor::Purple,InPerceptionInfo.PerceptionTickInterval);
	MULTITRACE_SHAPE_BYPROFILE(HitResults,InActor,TEXT("Pawn"),FCollisionShape::MakeSphere,
		InPerceptionInfo.Radius,CollisionParams);
	
	ActorDetected(HitResults,InActor);


}

void UPerformActionBox::DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo)
{

	if (!InActor) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(InActor);
	TArray<FHitResult> HitResults;

	DRAW_DEBUG(DrawDebugBox,InActor,SHAPE_DIMENSIONS(InPerceptionInfo.ShapeDimensions),
		FColor::Purple,InPerceptionInfo.PerceptionTickInterval);
	
	MULTITRACE_SHAPE_BYPROFILE(HitResults,InActor,TEXT("Pawn"),FCollisionShape::MakeBox,
		InPerceptionInfo.ShapeDimensions,CollisionParams);

	ActorDetected(HitResults,InActor);
}

void UPerformActionCapsule::DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo)
{
	if (!InActor) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(InActor);
	TArray<FHitResult> HitResults;

	DRAW_DEBUG(DrawDebugCapsule,InActor,SHAPE_DIMENSIONS(InPerceptionInfo.Height,InPerceptionInfo.Radius,FQuat::Identity),
	FColor::Purple,InPerceptionInfo.PerceptionTickInterval);
	
	MULTITRACE_SHAPE_BYPROFILE(HitResults,InActor,TEXT("Pawn"),FCollisionShape::MakeCapsule,
	SHAPE_DIMENSIONS(InPerceptionInfo.Height,InPerceptionInfo.Radius),CollisionParams);
	
	ActorDetected(HitResults,InActor);
}


void ActorDetected(const TArray<FHitResult>& InHitResults,const AActor* InActor)
{
	if(InHitResults.IsEmpty())return;
	for (const FHitResult& HitResult : InHitResults)
	{
		if(!HitResult.IsValidBlockingHit()) continue;
		InActor->GetWorld()->GetSubsystem<UPerceptionSubsystem>()->OnActorDetected.Execute(HitResult.GetActor());
	}
}