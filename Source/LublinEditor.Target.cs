// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class LublinEditorTarget : TargetRules
{
	public LublinEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        ExtraModuleNames.Add("Lublin");
	}

	//
	// TargetRules interface.
	//

}
