// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RadioButtonsWidgetStyle.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

FUNC_DECLARE_DELEGATE(FOnRadioChoiceChanged, int32)

class MYPROJECT_API SRadioButtons : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SRadioButtons)
	{}
	
	SLATE_ATTRIBUTE(int32, Count);

	SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void SetRadioButtonStyle(const FRadioButtonsStyle* InStyle);

	FOnRadioChoiceChanged OnRadioChoiceChanged;

	/*virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;*/

private:

	TAttribute<int32> Count;

	TSharedPtr<SVerticalBox> Holder;

	int32 CurrentChoice = 0;

	TAttribute<int32> maxCount = 10;

	TSharedRef<SWidget> CreateRadioButton(int32 RadioButtonChoice, FString RadioText);

	ECheckBoxState IsRadioButtonChecked(int32 RadioButtonID) const;

	void HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, int32 RadioButtonID);

	const FCheckBoxStyle* CheckBoxStyle = nullptr;

	const FTextBlockStyle* TextStyle = nullptr;

	const FRadioButtonsStyle* Style = nullptr;
};