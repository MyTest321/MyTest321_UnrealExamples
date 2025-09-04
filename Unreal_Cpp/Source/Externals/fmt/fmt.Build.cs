using UnrealBuildTool;

public class fmt : ModuleRules
{
    public fmt(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
		
        // Enable C++17
        CppStandard = CppStandardVersion.Cpp17;
        
        // Add include path
        PublicIncludePaths.Add(ModuleDirectory + "/include");
        
        // Disable problematic features that conflict with UE
        PublicDefinitions.AddRange(new string[] {
            "FMT_HEADER_ONLY=1",
            "FMT_USE_CONSTEXPR=0",
            "FMT_USE_NONTYPE_TEMPLATE_ARGS=0",
            "FMT_USE_USER_DEFINED_LITERALS=0",
            "FMT_USE_GRISU3=0",
            "FMT_USE_FLOAT128=0",
            "FMT_STRING_ALIAS=0",
			"FMT_EXCEPTIONS=0",
        });
    }
}