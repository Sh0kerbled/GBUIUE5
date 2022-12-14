// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Styling/SlateTypes.h"
#include "RadioButtonsWidgetStyle.generated.h"


USTRUCT()
struct MYPROJECT_API FRadioButtonsStyle : public FSlateWidgetStyle
{
	GENERATED_BODY()

	FRadioButtonsStyle();
	virtual ~FRadioButtonsStyle();

	UPROPERTY(EditAnywhere, Category = "Appearance")
		FCheckBoxStyle CheckBoxStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance")
		FTextBlockStyle TextStyle;

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FRadioButtonsStyle& GetDefault();
};

UCLASS(hidecategories=Object, MinimalAPI)
class UDeathButtonsWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:

	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FRadioButtonsStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
