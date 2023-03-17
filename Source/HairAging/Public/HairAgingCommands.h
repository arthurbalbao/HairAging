// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "HairAgingStyle.h"

class FHairAgingCommands : public TCommands<FHairAgingCommands>
{
public:

	FHairAgingCommands()
		: TCommands<FHairAgingCommands>(TEXT("HairAging"), NSLOCTEXT("Contexts", "HairAging", "HairAging Plugin"), NAME_None, FHairAgingStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};