// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CheckBox.h"
#include "DzienNocCheckbock.generated.h"

/**
 * 
 */
UCLASS()
class LUBLIN_API UDzienNocCheckbock : public UCheckBox
{
	GENERATED_BODY()
public:

protected:

		/*
		Toggles The Daytime
		uses Day variable to determine stage of toggle
		@Param *LightToChange jest swiatlem ktore musi byc przeskalowane w celu 
		zmieny dnia i nocy.
		*/
	UFUNCTION(BlueprintCallable, Category = "ZmianaDniaINocy")
		void ToggleDayNight(AActor *LightToChange, bool bCheckboxStatus);
	
		
};
