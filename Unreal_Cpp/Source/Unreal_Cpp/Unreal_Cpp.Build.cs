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

			//-- Unreal Module --
			"UMG",
			"Slate",
			"SlateCore",

			//-- Unreal Plugin --
//			"EnhancedInput", // required UE5.1 Manually: Edit -> Plugins -> Enable Enhanced Input

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
				"Unreal_Cpp/Example004",
				"Unreal_Cpp/Example005",
				"Unreal_Cpp/Example006",
				"Unreal_Cpp/Example007",
				"Unreal_Cpp/Example008",
			}
		);

		if (Target.bBuildEditor == true) {
			PrivateDependencyModuleNames.AddRange(new string[] {
				"UnrealEd",
			});
		}
	}
}
