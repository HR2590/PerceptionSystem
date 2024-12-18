// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerformActionBase.h"
#include "PerceptionComponent.generated.h"

class UPerformActionBase;
class UPerceptionSubsystem;
class UArrowComponent;


USTRUCT(BlueprintType)
struct FPerceptionInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	TSubclassOf<UPerformActionBase> SenseImplementation=UPerformActionBox::StaticClass();
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	UArrowComponent* ShapeLocation;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="PerceptionComponent")
	TArray<FName> AllSocketNames;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	FName SelectedSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	bool IsPerceptionActive=true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	float PerceptionTickInterval=1.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	FVector ShapeDimensions=FVector(100.f,100.f,80.f);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	float Height=100.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	float Radius=100.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	signed int Segments=25;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent",meta=(AllowPrivateAccess=true))
	bool IsDrawDebug=true;
};



UCLASS(BlueprintType,ClassGroup=(Custom))
class TAREAPERCEPCION_API UPerceptionComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY()
	UPerformActionBase* PerformObject;
	FTimerHandle TimerHandle;
	
	void AttachSKMesh(const FName& InSocketName);
	void GetAllSockets(TArray<FName>& OutSockets) const;
	USkeletalMeshComponent* GetSkeletonMesh() const;
public:
	// Sets default values for this component's properties
	UPerceptionComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PerceptionComponent")
	FPerceptionInfo PerceptionInfo;

	UFUNCTION()
	void PerformAction();
	void TimerStartWithInterval(const float InTimerInterval);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};


