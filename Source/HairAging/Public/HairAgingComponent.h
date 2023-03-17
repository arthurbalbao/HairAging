// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GroomAssetRendering.h"
#include "HairAgingComponent.generated.h"


UCLASS( Blueprintable )
class HAIRAGING_API UHairAgingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHairAgingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "HairAgingPlugin", meta = (Keywords = "set, hairgroups, geometrysettings"))
		static void	setHairGeometrySettings(UPARAM(ref) struct FHairGroupsRendering& hairGroups, FHairGeometrySettings geometrySettings);
		
};
