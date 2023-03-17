// Fill out your copyright notice in the Description page of Project Settings.


#include "HairAgingComponent.h"

// Sets default values for this component's properties
UHairAgingComponent::UHairAgingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHairAgingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHairAgingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UHairAgingComponent::setHairGeometrySettings(UPARAM(ref) struct FHairGroupsRendering& hairGroups,FHairGeometrySettings geometrySettings) {
	hairGroups.GeometrySettings = geometrySettings;
}
