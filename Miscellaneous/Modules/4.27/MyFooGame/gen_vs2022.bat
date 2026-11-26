@REM #change current directory to this file
%~d0
cd %~dp0

@set PROJECT_NAME=MyFooGame
@set uproject=%~dp0\%PROJECT_NAME%.uproject
@set UnrealBuildTool_exe="C:\Program Files\Epic Games\UE_4.27\Engine\Binaries\DotNET\UnrealBuildTool.exe"

%UnrealBuildTool_exe% -projectfiles -project="%uproject%" -Game -2022 -Progress

@pause