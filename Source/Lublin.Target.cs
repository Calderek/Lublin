// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class LublinTarget : TargetRules
{
	public LublinTarget(TargetInfo Target): base (Target)
	{
		Type = TargetType.Game;
        ExtraModuleNames.Add("Lublin");
    }

	//
	// TargetRules interface.
	//

}
