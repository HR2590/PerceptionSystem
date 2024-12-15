// Fill out your copyright notice in the Description page of Project Settings.


#include "PerformActionBase.h"
#include "PerceptionSubsystem.h"
#include "DrawDebugHelpers.h"
#include "PerceptionComponent.h"



void UPerformActionBase::DoAction(AActor* InActor, const FPerceptionInfo& InPerceptionInfo)
{
}

void UPerformActionSphere::DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo)
{
	if (!InActor) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(InActor);
	TArray<FHitResult> HitResults;
	DrawDebugSphere(
		GetWorld(), InActor->GetActorLocation(),
		InPerceptionInfo.Radius, InPerceptionInfo.Segments,
		FColor::Purple, false,InPerceptionInfo.PerceptionTickInterval);
	GetWorld()->SweepMultiByProfile(
		HitResults, InActor->GetActorLocation(),InActor->GetActorLocation(),
		FQuat::Identity ,TEXT("Pawn"),
		FCollisionShape::MakeSphere(InPerceptionInfo.Radius),CollisionParams);
	
	if(HitResults.IsEmpty())return;
	for (const FHitResult& HitResult : HitResults)
	{
		if(!HitResult.IsValidBlockingHit()) continue;
		InActor->GetWorld()->GetSubsystem<UPerceptionSubsystem>()->OnActorDetected.Execute(HitResult.GetActor());
	}


}

void UPerformActionBox::DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo)
{

	if (!InActor) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(InActor);
	TArray<FHitResult> HitResults;
	DrawDebugBox(
		GetWorld(), InActor->GetActorLocation(), InPerceptionInfo.ShapeDimensions,
		FColor::Purple, false,InPerceptionInfo.PerceptionTickInterval==0?-1:InPerceptionInfo.PerceptionTickInterval);
	GetWorld()->SweepMultiByProfile(
	HitResults, InActor->GetActorLocation(),InActor->GetActorLocation(),
	FQuat::Identity,TEXT("Pawn"),
	FCollisionShape::MakeBox(InPerceptionInfo.ShapeDimensions),CollisionParams);
	if(HitResults.IsEmpty())return;
	for (const FHitResult& HitResult : HitResults)
	{
		if(!HitResult.IsValidBlockingHit()) continue;
		InActor->GetWorld()->GetSubsystem<UPerceptionSubsystem>()->OnActorDetected.Execute(HitResult.GetActor());
	}
}

void UPerformActionCapsule::DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo)
{
	if (!InActor) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(InActor);
	TArray<FHitResult> HitResults;
	DrawDebugCapsule(
		GetWorld(), InActor->GetActorLocation(),
		InPerceptionInfo.Height,InPerceptionInfo.Radius,
		FQuat::Identity ,FColor::Purple, false,InPerceptionInfo.PerceptionTickInterval);
	GetWorld()->SweepMultiByProfile(
		HitResults, InActor->GetActorLocation(),InActor->GetActorLocation(),
		FQuat::Identity ,TEXT("Pawn"),
		FCollisionShape::MakeCapsule(InPerceptionInfo.Height,InPerceptionInfo.Radius),
		CollisionParams);
	
	if(HitResults.IsEmpty())return;
	for (const FHitResult& HitResult : HitResults)
	{
		if(!HitResult.IsValidBlockingHit()) continue;
		InActor->GetWorld()->GetSubsystem<UPerceptionSubsystem>()->OnActorDetected.Execute(HitResult.GetActor());
	}
}


