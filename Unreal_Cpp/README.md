# Unreal Cpp
- Getting started with Unreal C++ as a beginner

## Requirements
- Unreal Editor 5.0.3
- Visual Studio 2022/2019
- MSVC v143 - VS 2022 C++ x64/x86 build tool (v14.38-17.8) (Out of support)
- .NET Core 3.1 Runtime (Out of support)

### Maybe manually select MSVC version for UnrealBuildTool(UBT)
***UBT may not happy when you have multi MSVC version in VS2022, cuz it default use higher version to compile.***

- Open **%APPDATA%/Unreal Engine/UnrealBuildTool/BuildConfiguration.xml** and modify kind of
```xml
<?xml version="1.0" encoding="utf-8"?>
<Configuration xmlns="https://www.unrealengine.com/BuildConfiguration">
    <WindowsPlatform>
        <!-- Please Replace Your MSVC version !! -->
        <!-- Check Your MSVC version: "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC" !!-->
        <CompilerVersion>14.38.33130</CompilerVersion>
    </WindowsPlatform>
</Configuration>
```

## How to Build
- Run `gen_vs2022.bat` or `gen_vs2019.bat`
- Open `Unreal_Cpp.sln` and Compile/Run

## References
- https://www.youtube.com/watch?v=JYr0auU4HEw&list=PLeGk08zVu457Bkp3EYRqTP0QHue9T0drG