// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PerformActionBase.generated.h"

struct FPerceptionInfo;
/**
 * 
 */
UCLASS()
class TAREAPERCEPCION_API UPerformActionBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo);
};

UCLASS(BlueprintType,Blueprintable)
class TAREAPERCEPCION_API UPerformActionSphere : public UPerformActionBase
{
	GENERATED_BODY()
public:
	virtual void DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo) override;
};

UCLASS(BlueprintType,Blueprintable)
class TAREAPERCEPCION_API UPerformActionBox : public UPerformActionBase
{
	GENERATED_BODY()
public:
	virtual void DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo) override;
};

UCLASS(BlueprintType,Blueprintable)
class TAREAPERCEPCION_API UPerformActionCapsule : public UPerformActionBase
{
	GENERATED_BODY()
public:
	virtual void DoAction(AActor* InActor,const FPerceptionInfo& InPerceptionInfo) override;
};