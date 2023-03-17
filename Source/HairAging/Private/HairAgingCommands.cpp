// Copyright Epic Games, Inc. All Rights Reserved.

#include "HairAgingCommands.h"

#define LOCTEXT_NAMESPACE "FHairAgingModule"

void FHairAgingCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "HairAging", "Bring up HairAging window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
