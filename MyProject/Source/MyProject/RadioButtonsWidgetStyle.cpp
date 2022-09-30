// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtonsWidgetStyle.h"

FRadioButtonsStyle::FRadioButtonsStyle()
{
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("RadioButton");
	TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalUnderlinedText");
}

FRadioButtonsStyle::~FRadioButtonsStyle()
{
}

const FName FRadioButtonsStyle::TypeName(TEXT("FRadioButtonsStyle"));

const FRadioButtonsStyle& FRadioButtonsStyle::GetDefault()
{
	static FRadioButtonsStyle Default;
	return Default;
}

void FRadioButtonsStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	FSlateWidgetStyle::GetResources(OutBrushes);

	CheckBoxStyle.GetResources(OutBrushes);
	TextStyle.GetResources(OutBrushes);
}

