// Fill out your copyright notice in the Description page of Project Settings.
#define LOCTEXT_NAMESPACE "AgingWidget"

#include "SAgingWidget.h"
#include "SlateOptMacros.h"

void SAgingWidget::OnSegmentationCheckBoxChanged(ECheckBoxState NewState)
{
	bUseCustomSegmentation = NewState == ECheckBoxState::Checked ? true : false;
}

ECheckBoxState SAgingWidget::IsSegmentationBoxChecked() const
{
	return bUseCustomSegmentation ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

FReply SAgingWidget::OnChooseNormalMapButtonClicked()
{
	const FString DialogTitle;
		const FString DefaultPath;
		const FString FileTypes;
		TArray<FString> OutFileNames;

	void* ParentWindowPtr = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		uint32 SelectionFlag = 0;
		DesktopPlatform->OpenFileDialog(ParentWindowPtr, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag, OutFileNames);
		if (!(OutFileNames.IsEmpty())) {
			std::string path = std::string(TCHAR_TO_UTF8(*(OutFileNames[0])));
			if (checkImgDims(path, TEXSIZE, TEXSIZE) == true) {
				customMapPath = OutFileNames[0];
				FText title = FText::FromString("Hair Aging Plugin");
				FText msg = FText::FromString("Custom normal map sucessfully selected!");
				UEditorDialogLibrary::ShowMessage(title, msg, EAppMsgType::Ok, EAppReturnType::Ok);
			}
			else {
				FText title = FText::FromString("Hair Aging Plugin");
				FFormatNamedArguments Args;
				Args.Add(TEXT("Size"), TEXSIZE);
				FText msg = FText::Format(LOCTEXT("ErrorImgSize", "Only {Size} x {Size} images are accepted! "), Args);
				UEditorDialogLibrary::ShowMessage(title, msg, EAppMsgType::Ok, EAppReturnType::Ok);
			}
			
		}
	}
	return FReply::Handled();
}

FReply SAgingWidget::OnGenerateMIButtonClicked()
{
	Mat new_centroids;

	Mat labels;
	int map_cluster_to_region[8];

	if (boxText.IsEmpty()) {
		FText title = FText::FromString("Hair Aging Plugin");
		FText msg = FText::FromString("Must insert a name for the character.");
		UEditorDialogLibrary::ShowMessage(title, msg, EAppMsgType::Ok, EAppReturnType::Ok);
		return FReply::Handled();
	}

	if (bUseCustomSegmentation) {
		if (customMapPath.IsEmpty()) {
			FText title = FText::FromString("Hair Aging Plugin");
			FText msg = FText::FromString("Custom normal map not selected");
			UEditorDialogLibrary::ShowMessage(title, msg, EAppMsgType::Ok, EAppReturnType::Ok);
			return FReply::Handled();
		}
		labels = Segmentation(std::string(TCHAR_TO_UTF8(*(customMapPath))), &new_centroids, boxText.ToString());
		determineHeadRegionforClusters(new_centroids, map_cluster_to_region);
	}
	
	agingScale = calcBiologicalAgingRate(agingScale);

	UTexture2D* parameterTex = createParameterTexture(labels, agingScale, map_cluster_to_region, bIsMaleCharacter, bUseCustomSegmentation, boxText.ToString());
	
	if (createAgingMatInstances(parameterTex, agingScale, boxText.ToString())) {
		FNotificationInfo Info(FText::FromString("Hair Aging Material Instance successfully created!"));
		Info.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Couldn't create material instance"));

	return FReply::Handled();
}

void SAgingWidget::setAgingAlpha(const float value) {
	agingScale = value;
}

void SAgingWidget::onRadioButtonCheckStateChanged(ECheckBoxState new_state, ERadioChoice buttonState) 
{
	if (new_state == ECheckBoxState::Checked)
	{
		currentChoice = buttonState;

		if (currentChoice == MALE)
			bIsMaleCharacter = true;
		else
			bIsMaleCharacter = false;
	}
}

ECheckBoxState SAgingWidget::IsRadioButtonChecked(ERadioChoice buttonID) const
{
	return (currentChoice == buttonID) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;

}

void SAgingWidget::OnTextChanged(const FText& text) {
	boxText = text;
}


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SAgingWidget::Construct(const FArguments& InArgs)
{
	this->ChildSlot[
		SNew(SVerticalBox)
			
		+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Hair Aging Rate"))
				.ToolTipText(FText::FromString("Defines the hair aging rate, from early to late greying"))
			]
		+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
				[
					SNew(SSlider)
				.StepSize(.05f)
				.Value(.5f)
				.MouseUsesStep(true)
				.Locked(false)
				.OnValueChanged(this,&SAgingWidget::setAgingAlpha)
				]
			]

		+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(FMargin(0, 5, 0, 0))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Gender"))
			]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Right)
			[
				SNew(SCheckBox)
				.Style(FCoreStyle::Get(), "RadioButton")
				.IsChecked(this, &SAgingWidget::IsRadioButtonChecked,FEMALE)
				.OnCheckStateChanged(this, &SAgingWidget::onRadioButtonCheckStateChanged, FEMALE)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Female"))
				
				]
			]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				[
					SNew(SCheckBox)
					.Style(FCoreStyle::Get(), "RadioButton")
				.IsChecked(this, &SAgingWidget::IsRadioButtonChecked, MALE)
				.OnCheckStateChanged(this, &SAgingWidget::onRadioButtonCheckStateChanged, MALE)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Male"))
				]
			]
		]
		+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Use Custom Normal Map for Segmentation"))
					.ToolTipText(FText::FromString("Otherwise uses default segmentation that works for most heads"))
				]
		+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
				[
				SNew(SCheckBox)
				.OnCheckStateChanged(this, &SAgingWidget::OnSegmentationCheckBoxChanged)
				.IsChecked(this, &SAgingWidget::IsSegmentationBoxChecked)
				]
			]
		+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(FMargin(0, 5, 0, 0))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Choose custom normal map"))
					.ToolTipText(FText::FromString("Normal map must be in object space coordinates"))
				]
		+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
				[
					SNew(SButton)
					.Text(FText::FromString("Browse normal map file"))
				.OnClicked(FOnClicked::CreateSP(this, &SAgingWidget::OnChooseNormalMapButtonClicked))
				]
			]

		+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(FMargin(0, 5, 0, 0))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Input Character Name"))
			]
		+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
					[
					SNew(SEditableTextBox)
					.HintText(FText::FromString("Character Name"))
					.OnTextChanged(this,&SAgingWidget::OnTextChanged)
					]
			]

		+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(FMargin(0, 20, 0, 0))
			[
				SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				[
						SNew(SButton)
						.Text(FText::FromString("Create Hair Aging Material Instance"))
					.ToolTipText(FText::FromString("Normal map must be in object space coordinates"))
					.OnClicked(FOnClicked::CreateSP(this, &SAgingWidget::OnGenerateMIButtonClicked))
				]
			]

	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE