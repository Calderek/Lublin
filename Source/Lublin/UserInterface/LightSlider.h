// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "LightSlider.generated.h"

/**
 * 
 */
UCLASS()
class LUBLIN_API ULightSlider : public USlider
{
	GENERATED_BODY()
protected:

	/*
	Zmiana stanu naswietlenia w zaleznosci od suwaka
	Parametry:
	LightToChange - swiatlo ktore zostanie zmienione)
	float fLightValie - zmienna okreslajaca intesywnosc dla swiatla dla swiatla
	z zakresu od 0 do 1.00 (skylight)
	0 do 2,75 (directionalLight)
	*/
	UFUNCTION(BlueprintCallable, Category = "ZmianaDniaINocy")
		void changeLightValue(AActor *LightToChange, float fLightValue);

	
	
	
};
