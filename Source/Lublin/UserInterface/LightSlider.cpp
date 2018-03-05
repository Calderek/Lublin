// Fill out your copyright notice in the Description page of Project Settings.

#include "Lublin.h"
#include "LightSlider.h"
#include "Classes/Components/SkyLightComponent.h"
#include "Classes/Components/LightComponent.h"





void  ULightSlider::changeLightValue(AActor *LightToChange, float fLightValue)
{
	/*przerzutuj dwa swiatla zeby sprawdzic ich typy*/
	ASkyLight* Test = Cast<ASkyLight>(LightToChange);
	ADirectionalLight* Test2 = Cast<ADirectionalLight>(LightToChange);
	// Jesli swiatlo jest SkyLightem to
	if (Test)
	{
		// Wyluskaj Component odpowiedzialny za oswietlenie
		USkyLightComponent* LightComp = Test->GetLightComponent();
		// Zmien intesywnosc swiatla
		LightComp->SetIntensity(fLightValue);
		
	}
	// Jezeli rzut na directionalLight sie udal to
	else if (Test2)
	{
		//przeskalowanie suwaka na wartosci dla directional Light
		fLightValue *= 1.75;
		ULightComponent* LightComp = Test2->GetLightComponent();
		LightComp->SetIntensity(fLightValue);
	}
}