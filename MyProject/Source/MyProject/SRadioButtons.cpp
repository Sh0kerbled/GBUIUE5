// Fill out your copyright notice in the Description page of Project Settings.


#include "SRadioButtons.h"
#include "SlateOptMacros.h"
#include "RadioButtons.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Text/STextBlock.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRadioButtons::Construct(const FArguments& InArgs)
{
	Count = InArgs._Count;
	SetRadioButtonStyle(InArgs._Style);

	ChildSlot
		[
			SAssignNew(Holder,SVerticalBox)
			+ SVerticalBox::Slot()
	//	[
	//		// first radio button
	//		CreateRadioButton(0, TEXT("Gold Trigger"))
	//	]
	//+ SVerticalBox::Slot()
	//	[
	//		// second radio button
	//		CreateRadioButton(1, TEXT("Gold Digger"))
	//	]
	//+ SVerticalBox::Slot()
	//	[
	//		// third radio button
	//		CreateRadioButton(2, TEXT("GOLD NIGG"))
	//	]
		];

	Holder->ClearChildren();
	for(int32 i = 0; i<Count.Get(); i++)
	{
		Holder->AddSlot()
		[
			CreateRadioButton(i, TEXT("Karoche hz") + FString::FromInt(i))
		];
	}
}

void SRadioButtons::SetRadioButtonStyle(const FRadioButtonsStyle* InStyle)
{
	CheckBoxStyle = &InStyle->CheckBoxStyle;
	TextStyle = &InStyle->TextStyle;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<SWidget> SRadioButtons::CreateRadioButton(int32 RadioButtonChoice, FString RadioText)
{
	return SNew(SCheckBox)
		.IsChecked_Raw(this, &SRadioButtons::IsRadioButtonChecked,
			RadioButtonChoice)
		.OnCheckStateChanged_Raw(this, &SRadioButtons::HandleRadioButtonStateChanged,
			RadioButtonChoice)
		.Style(CheckBoxStyle)
		[
			SNew(STextBlock)
			.Text(FText::FromString(RadioText))
		.TextStyle(TextStyle)
		];
}

ECheckBoxState SRadioButtons::IsRadioButtonChecked(int32 RadioButtonID) const
{
	return (CurrentChoice == RadioButtonID) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}


void SRadioButtons::HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, int32 RadioButtonID)
{
	if (NewRadioState == ECheckBoxState::Checked)
	{
		CurrentChoice = RadioButtonID;
		/*HandleRadioButtonStateChanged.ExecuteIfBound(CurrentChoice);*/
	}
}


