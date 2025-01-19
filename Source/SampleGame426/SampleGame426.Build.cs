// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class SampleGame426 : ModuleRules
{
	public SampleGame426(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
		
		PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "multiprecision", "include"));
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Immutable",
			"ImmutableOrderbook", 
			"ImmutablezkEVMAPI",
			"ImmutableMarketplace",
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{  
			"SlateCore",
			"Slate",
			"UMG",
			"GameplayTags",
			"DeveloperSettings",
			"Json",
			"JsonUtilities",
			"HTTP",
		});

		PrivateIncludePaths.AddRange(new string[]
		{
			"SampleGame426/Public/UI",
		});
	}
}
