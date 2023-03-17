// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "GroomTextureBuilder.h"
#include "UObject/Object.h"
#include "Widgets/SCompoundWidget.h"
#include "IDesktopPlatform.h"
#include "Framework/Application/SlateApplication.h"
#include "PropertyCustomizationHelpers.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "HeadSegmentation.h"
#include "GroomAsset.h"
#include "UObject/SoftObjectPath.h"
#include "ImageUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "GameFramework/Actor.h"
#include "Internationalization/Text.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/Material.h"
#include "Engine/Texture.h"
#include "UObject/ConstructorHelpers.h"
#include "AssetToolsModule.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "AgingFactorsCalc.h"
#include "Containers/Array.h"
#include "Widgets/Input/SSlider.h"
#include "Interfaces/IPluginManager.h"
#include "Framework/Notifications/NotificationManager.h"
#include "HairAgingUtils.h"
#include "EditorDialogLibrary.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "RHI.h"
#include "AgingParameters.h"
#include <string>

enum ERadioChoice {
	MALE,
	FEMALE
};

ERadioChoice currentChoice;


class  SAgingWidget : public SCompoundWidget
{
private:
	FString ContentPath = IPluginManager::Get().FindPlugin(TEXT("HairAging"))->GetContentDir();
	float agingScale = 1.f;
	FText boxText;
	FString customMapPath;
public:
	SLATE_BEGIN_ARGS(SAgingWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	FReply OnChooseNormalMapButtonClicked();
	FReply OnGenerateMIButtonClicked();
	void setAgingAlpha(const float value);
	ECheckBoxState IsRadioButtonChecked(ERadioChoice buttonID) const;
	void onRadioButtonCheckStateChanged(ECheckBoxState new_state, ERadioChoice buttonState) ;
	void OnSegmentationCheckBoxChanged(ECheckBoxState NewState);
	void OnTextChanged(const FText& text);
	ECheckBoxState IsSegmentationBoxChecked() const;

protected:
	bool bUseCustomSegmentation;
		bool bIsTestBoxChecked;
		bool bIsMaleCharacter = true;

};
