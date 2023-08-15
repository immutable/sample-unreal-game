// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class endlessrunTarget : TargetRules
{
	public endlessrunTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "endlessrun" } );
		bOverrideBuildEnvironment = true;
		AdditionalCompilerArguments = "-Wno-bitwise-instead-of-logical -Wno-unused-but-set-variable";
	}
}
