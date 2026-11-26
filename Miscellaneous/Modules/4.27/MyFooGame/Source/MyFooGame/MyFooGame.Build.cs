using UnrealBuildTool;

public class MyFooGame : ModuleRules
{
	public MyFooGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "MyFooGame-pch.h";
		
		PublicDependencyModuleNames.AddRange(new string[] {
			// --- My Plugins ---
			"FooBar"

			// --- My Modules ---
			, "MyCore"
			, "MyRender"
			, "MyUI"
			// --- My Modules Test---
			, "MyTest"

			// --- Common ---
            , "ApplicationCore"
			, "Projects"
			// --- UMG / Slate ---
			, "SlateCore"
			, "Slate"
			, "UMG"
			// --- Default ---
			, "Core"
			, "CoreUObject"
			, "Engine"
			, "InputCore" // "EnhancedInput"
			, "HeadMountedDisplay"
		});

#if false
		PublicIncludePaths.AddRange(new string[] {
				//-- Common --
				Path.Combine(ModuleDirectory, "MyLib")
				, Path.Combine(ModuleDirectory, "Misc")
				, Path.Combine(ModuleDirectory, "Tests")
				//-- Weeks --
				, Path.Combine(ModuleDirectory, "Week001")
				, Path.Combine(ModuleDirectory, "Week002")
			}
		);
#endif
		
		if (Target.bBuildEditor == true) {
			PrivateDependencyModuleNames.AddRange(new string[] {
				"UnrealEd"
				, "MainFrame"
			});
		}
	}
}
