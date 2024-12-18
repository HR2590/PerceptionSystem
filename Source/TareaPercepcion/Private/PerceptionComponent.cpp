// Fill out your copyright notice in the Description page of Project Settings.
#include "PerceptionComponent.h"
#include "PerformActionBase.h"
#include "Components/ArrowComponent.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"


// Sets default values for this component's properties
UPerceptionComponent::UPerceptionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval=0.0f;

}


// Called when the game starts
void UPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();
	if (!PerceptionInfo.SenseImplementation) return;
	PerformObject = NewObject<UPerformActionBase>(this,PerceptionInfo.SenseImplementation);
	TimerStartWithInterval(PerceptionInfo.PerceptionTickInterval);
}


void UPerceptionComponent::PerformAction()
{
	TimerStartWithInterval(PerceptionInfo.PerceptionTickInterval);
	if (!PerceptionInfo.SenseImplementation)return;
	if (PerceptionInfo.SenseImplementation!=PerformObject->GetClass())
	{
		PerformObject->ConditionalBeginDestroy();
		PerformObject = NewObject<UPerformActionBase>(this,PerceptionInfo.SenseImplementation);
	}
	if (PerceptionInfo.IsPerceptionActive)PerformObject->DoAction(GetOwner(),PerceptionInfo);
	
	
}

void UPerceptionComponent::TimerStartWithInterval(const float InTimerInterval)
{
	if (TimerHandle.IsValid())TimerHandle.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(
	TimerHandle,this,&ThisClass::PerformAction,InTimerInterval,false);
	
}


void UPerceptionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	TimerHandle.Invalidate();
}

void UPerceptionComponent::AttachSKMesh(const FName& InSocketName)
{
	if (PerceptionInfo.AllSocketNames.IsEmpty()||!GetSkeletonMesh())return;
	if (PerceptionInfo.AllSocketNames.Contains(InSocketName))
	{
		UE_LOG(LogTemp,Warning,TEXT("true"));
		PerceptionInfo.ShapeLocation->AttachToComponent(GetSkeletonMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,InSocketName);
		
	}
}

void UPerceptionComponent::GetAllSockets(TArray<FName>& OutSockets) const
{
	if (!GetSkeletonMesh())return;
	OutSockets.Empty();
	OutSockets.Append(GetSkeletonMesh()->GetAllSocketNames());

}

USkeletalMeshComponent* UPerceptionComponent::GetSkeletonMesh() const
{
	if (!GetOwner()) return nullptr;
		return GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}














