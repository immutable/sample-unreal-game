// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SampleGame426 : ModuleRules
{
	public SampleGame426(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{  
			"SlateCore",
			"Slate",
			"UMG",
			"GameplayTags",
			"DeveloperSettings",
			"Immutable",
			"Json",
			"JsonUtilities",
			"HTTP",
			"OpenAPI"
		});


		PrivateIncludePaths.AddRange(new string[]
		{
			"SampleGame426/Public/UI",
			"SampleGame426/Public/Online"

		});
	}
}
