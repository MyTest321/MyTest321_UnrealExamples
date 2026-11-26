using System.IO;
using UnrealBuildTool;

public class MyRender : ModuleRules
{
    public MyRender(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "src/MyRender-pch.h";

		PublicIncludePaths.AddRange(new string[] { 
            Path.Combine(ModuleDirectory, "src")
        });

        PublicDependencyModuleNames.AddRange(new string[] {
            "MyCore"

            // --- Rendering ---
			, "RenderCore"
			, "RHI"
			, "Niagara"
			// --- Default ---
			, "Core"
        });
    }
}