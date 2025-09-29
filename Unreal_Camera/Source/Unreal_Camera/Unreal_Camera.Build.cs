// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal_Camera : ModuleRules
{
	public Unreal_Camera(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivatePCHHeaderFile = "Unreal_Camera_PCH.h";

		PublicDependencyModuleNames.AddRange(new string[] {
			//-- UI --
			"UMG",
			"Slate",
			"SlateCore",

			//-- Default --
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput"
		});
		
		PublicIncludePaths.AddRange(
			new string[] {
				"Unreal_Camera/Example001", // Ref: https://www.youtube.com/watch?v=waW1yLh-o5E
				"Unreal_Camera/Example002", // Ref: https://github.com/SimpleTalkCpp/SimpleTalkCpp_UnrealExamples/tree/main/ThirdPerson_FixedCamera
				"Unreal_Camera/Example003", // Ref: https://dev.epicgames.com/documentation/en-us/unreal-engine/using-a-static-camera-in-unreal-engine
				"Unreal_Camera/Example004", // Ref: https://dev.epicgames.com/documentation/en-us/unreal-engine/switching-between-multiple-fixed-camera-perspectives-in-unreal-engine
			}
		);
		
		if (Target.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.AddRange(new string[] {
				"UnrealEd",
			});
		}
	}
}
