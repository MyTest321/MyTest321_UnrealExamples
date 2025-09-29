@REM #change current directory to this file
%~d0
cd %~dp0

@set PROJECT_NAME=Unreal_Camera
@set uproject=%~dp0\%PROJECT_NAME%.uproject
@set UnrealBuildTool_exe="C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"

%UnrealBuildTool_exe% -projectfiles -project="%uproject%" -game -2022 -progress

@pause