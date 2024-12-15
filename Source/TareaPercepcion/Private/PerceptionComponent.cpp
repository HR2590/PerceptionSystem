// Fill out your copyright notice in the Description page of Project Settings.
#include "PerceptionComponent.h"
#include "PerformActionBase.h"


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
	auto Lambda = [this](){};
	if (!PerceptionInfo.USenseImplementation) return;
	PerformObject = NewObject<UPerformActionBase>(this,PerceptionInfo.USenseImplementation);
	OnTimerEvent.AddUObject(this, &UPerceptionComponent::OnPerformAction);
	OnTimerEvent.AddUObject(this, &UPerceptionComponent::OnTimerCheck);
	GetWorld()->GetTimerManager().SetTimer(
	TimerHandle,[this]()->void{this->OnTimerEvent.Broadcast();}
	,PerceptionInfo.PerceptionTickInterval,true);
	
	

	
	


}

// Called every frame
void UPerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPerceptionComponent::OnPerformAction()
{
	if (!PerceptionInfo.IsPerceptionActive||!PerceptionInfo.USenseImplementation) return;
	if (PerceptionInfo.USenseImplementation!=PerformObject->GetClass())
	{
		PerformObject->ConditionalBeginDestroy();
		PerformObject = NewObject<UPerformActionBase>(this,PerceptionInfo.USenseImplementation);
	}
	PerformObject->DoAction(GetOwner(),PerceptionInfo);
	
}

void UPerceptionComponent::OnTimerCheck()
{
	if (PerceptionInfo.PerceptionTickInterval!=GetWorld()->GetTimerManager().GetTimerRate(TimerHandle))
	{
		TimerHandle.Invalidate();
		GetWorld()->GetTimerManager().SetTimer(
	TimerHandle,[this]()->void{this->OnTimerEvent.Broadcast();}
	,PerceptionInfo.PerceptionTickInterval,true);
	}
}

void UPerceptionComponent::SetPerception(const bool& InStatus)
{
	PerceptionInfo.IsPerceptionActive=InStatus;
}

void UPerceptionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	TimerHandle.Invalidate();
}









