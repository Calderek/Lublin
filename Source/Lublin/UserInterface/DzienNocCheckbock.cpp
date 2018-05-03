// Fill out your copyright notice in the Description page of Project Settings.

#include "Lublin.h"
#include "DzienNocCheckbock.h"




void UDzienNocCheckbock::ToggleDayNight(AActor *LightToChange, bool bCheckboxStatus)
{
	/*przerzutuj dwa swiatla zeby sprawdzic ich typy
	w wypadku nullptr rzut zwroci nullptr takze zabezpiecza wskazniki :)*/
	ASkyLight* Test = Cast<ASkyLight>(LightToChange);
	ADirectionalLight* Test2 = Cast<ADirectionalLight>(LightToChange);
	/* Jesli checkbox jest tickniety, zmien na noc
	*/
	if (bCheckboxStatus)
	{
		// Jesli rzut sie uda³ to
		if (Test)
		{
			// Wyluskaj Component odpowiedzialny za oswietlenie
			USkyLightComponent* LightComp = Test->GetLightComponent();
			// Zmien intesywnosc swiatla
			LightComp->SetIntensity(0.1f);

		}
		// Jezeli rzut na directionalLight sie udal to
		if (Test2)
		{
			//przeskalowanie suwaka na wartosci dla directional Light
			ULightComponent* LightComp = Test2->GetLightComponent();
			// Zmien intesywnosc swiatla
			LightComp->SetIntensity(0.175f);
		}
	}
	// dla nieztickowanego ustaw dzien 
	else
	{

		if (Test)
		{
			// Wyluskaj Component odpowiedzialny za oswietlenie
			USkyLightComponent* LightComp = Test->GetLightComponent();
			// Zmien intesywnosc swiatla
			LightComp->SetIntensity(1.0f);

		}
		// Jezeli rzut na directionalLight sie udal to
		if (Test2)
		{
			//przeskalowanie suwaka na wartosci dla directional Light
			
			ULightComponent* LightComp = Test2->GetLightComponent();
			LightComp->SetIntensity(1.75f);
		}
	}


}
