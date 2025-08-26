// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal_Cpp : ModuleRules
{
	public Unreal_Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivatePCHHeaderFile = "Unreal_Cpp_PCH.h";

		PublicDependencyModuleNames.AddRange(new string[] {
			//-- Externals --
			"fmt",
		
			//-- Default --
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay"
		});
		
		PublicIncludePaths.AddRange(
			new string[] {
				"Unreal_Cpp/Example001",
				"Unreal_Cpp/Example002",
				"Unreal_Cpp/Example003",
			}
		);

		if (Target.bBuildEditor == true) {
			PrivateDependencyModuleNames.AddRange(new string[] {
				"UnrealEd",
			});
		}
	}
}
