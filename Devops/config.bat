@echo off

rem Find UE and Launcher
FOR /F "tokens=2* skip=2" %%a in ('reg query "HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine\5.1" /v "InstalledDirectory"') do set EnginePath=%%b

if not exist "%EnginePath%" (
	@echo "UE5.1 Is not installed. Unable to proceed"
	pause
	exit
	)

echo EnginePath="%EnginePath%"

rem Project
set ProjectRoot=%~dp0..
set ProjectPureName=PirateClicker

rem Unreal path
set RunUATPath=%EnginePath%\Engine\Build\BatchFiles\RunUAT.bat
set UBTRelativePath=%EnginePath%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe
set EditorUE=%EnginePath%\Engine\Binaries\Win64\UE4Editor.exe

rem Path to Project
set ProjectName=%ProjectPureName%.uproject
set ProjectPath=%ProjectRoot%\\%ProjectName%
