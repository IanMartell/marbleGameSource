// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class STestSlate : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(STestSlate) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_END_ARGS()

		//every widget needs a construction function
	void Construct(const FArguments& InArgs);
	
	FReply OnPlayClicked() const;
	FReply OnQuitClicked() const;
	
	TWeakObjectPtr<class ATestHud> OwningHUD;
	
	virtual bool SupportsKeyboardFocus() const override { return true; };
};