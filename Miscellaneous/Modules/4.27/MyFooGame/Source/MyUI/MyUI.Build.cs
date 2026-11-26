using System.IO;
using UnrealBuildTool;

public class MyUI : ModuleRules
{
    public MyUI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "src/MyUI-pch.h";

		PublicIncludePaths.AddRange(new string[] { 
            Path.Combine(ModuleDirectory, "src")
        });

        PublicDependencyModuleNames.AddRange(new string[] {
	        "MyCore"
            , "MyRender"

            // --- UMG / Slate ---
			, "SlateCore"
			, "Slate"
			, "UMG"
			// --- Default ---
			, "Core"
        });
    }
}