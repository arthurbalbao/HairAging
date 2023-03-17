// Copyright Epic Games, Inc. All Rights Reserved.

#include "HairAging.h"
#include "SAgingWidget.h"
#include "HairAgingStyle.h"
#include "HairAgingCommands.h"
#include "HeadSegmentation.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "..\Public\HairAging.h"

static const FName HairAgingTabName("HairAging");

#define LOCTEXT_NAMESPACE "FHairAgingModule"

void FHairAgingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FHairAgingStyle::Initialize();
	FHairAgingStyle::ReloadTextures();

	FHairAgingCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FHairAgingCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FHairAgingModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FHairAgingModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(HairAgingTabName, FOnSpawnTab::CreateRaw(this, &FHairAgingModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FHairAgingTabTitle", "HairAging"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FHairAgingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FHairAgingStyle::Shutdown();

	FHairAgingCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(HairAgingTabName);
}

TSharedRef<SDockTab> FHairAgingModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FHairAgingModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("HairAging.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SAgingWidget)
		];
		
}




void FHairAgingModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(HairAgingTabName);
}

void FHairAgingModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FHairAgingCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FHairAgingCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHairAgingModule, HairAging)