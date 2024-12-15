// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceptionSubsystem.h"
#include "PerceptionComponent.h"



void UPerceptionSubsystem::RegisterNewActor(AActor* InActor)
{
	if(IsPerceptionActive(InActor))AllDetectedActors.AddUnique(InActor);
	else RemoveActor(InActor);
	
}

void UPerceptionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//GetWorld()->AddOnActorDestroyedHandler(FOnActorSpawned::FDelegate::CreateUObject(this,&ThisClass::RemoveActor));
	OnActorDetected.BindUObject(this,&ThisClass::RegisterNewActor);
	
}
	

void UPerceptionSubsystem::Deinitialize()
{
	Super::Deinitialize();
	OnActorDetected.Unbind();

}

bool UPerceptionSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UPerceptionSubsystem::RemoveActor(AActor* InActor)
{
	AllDetectedActors.Remove(InActor);
}


bool UPerceptionSubsystem::IsPerceptionActive(const AActor* InActor)
{
	if (!InActor||!InActor->GetComponentByClass<UPerceptionComponent>()) return false;
	return InActor->FindComponentByClass<UPerceptionComponent>()->PerceptionInfo.IsPerceptionActive;
}



