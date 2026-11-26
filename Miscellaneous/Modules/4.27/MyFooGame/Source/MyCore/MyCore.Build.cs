using System.IO;
using UnrealBuildTool;

public class MyCore : ModuleRules
{
    public MyCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "src/MyCore-pch.h";

        PublicIncludePaths.AddRange(new string[] { 
            Path.Combine(ModuleDirectory, "src")
        });

#if false
        PrivateDependencyModuleNames.AddRange(new string[] {
            //-- external --
			"fmt"
        });
#endif

        PublicDependencyModuleNames.AddRange(new string[] {
	        //-- external --
			"fmt"

	        // --- Default ---> Only Added Unreal Engine Module What you needed.
	        , "Core"
	        , "CoreUObject"
	        , "Engine"
	        //, "InputCore" // "EnhancedInput"
	        //, "HeadMountedDisplay"
        });

        if (Target.bBuildEditor == true) {
			PublicDependencyModuleNames.AddRange(new string[] {
				"UnrealEd"
				, "MainFrame"
			});
		}
    }
}