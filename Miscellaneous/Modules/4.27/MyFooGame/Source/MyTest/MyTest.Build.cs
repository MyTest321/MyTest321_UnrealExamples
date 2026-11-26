using System.IO;
using UnrealBuildTool;

public class MyTest : ModuleRules
{
    public MyTest(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "src/MyTest-pch.h";

        PublicIncludePaths.AddRange(new string[] { 
            Path.Combine(ModuleDirectory, "src"),
        });

        PublicDependencyModuleNames.AddRange(new string[] {
	        "MyCore"
	        , "MyRender"
	        , "MyUI"

	        // --- Default ---
	        , "Core"
	        , "CoreUObject"
	        , "Engine"
//	        , "InputCore" // "EnhancedInput"
//	        , "HeadMountedDisplay"
        });


        if (Target.bBuildEditor == true) {
			PublicDependencyModuleNames.AddRange(new string[] {
				"UnrealEd"
				, "MainFrame"
			});
		}
    }
}