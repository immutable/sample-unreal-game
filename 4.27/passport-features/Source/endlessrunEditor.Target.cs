// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class endlessrunEditorTarget : TargetRules
{
	public endlessrunEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "endlessrun" } );
		bOverrideBuildEnvironment = true;
		AdditionalCompilerArguments = "-Wno-bitwise-instead-of-logical -Wno-unused-but-set-variable";
	}
}
