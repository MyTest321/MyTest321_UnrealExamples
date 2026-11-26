// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class FooBar : ModuleRules
{
	public FooBar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "src/FooBar-pch.h";

		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "src") // Path.Combine(PluginDirectory, "Source/FooBar/src")
			}
		);
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
		);
			
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// --- Default ---
				"Core",
			}
		);
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
#if false
				// --- Default ---
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
#endif
 				"CoreUObject",
				"Engine",
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}
