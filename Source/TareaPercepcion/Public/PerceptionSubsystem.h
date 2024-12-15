// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PerceptionSubsystem.generated.h"
DECLARE_DELEGATE_OneParam(FOnActorDetected,AActor*);



UCLASS(Blueprintable,BlueprintType,meta=(BlueprintSpawnableComponent))
class TAREAPERCEPCION_API UPerceptionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	void RegisterNewActor(AActor* InActor);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	UPROPERTY() TArray<AActor*> AllDetectedActors;
	void RemoveActor(AActor* InActor);
	static bool IsPerceptionActive(const AActor* InActor);
	
public:
	FOnActorDetected OnActorDetected;

};
