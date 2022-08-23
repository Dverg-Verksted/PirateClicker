@echo off

rem Edit param
set EnginePath=D:\UE_4.27
set LauncherEpicGames=C:\Program Files (x86)\Epic Games\Launcher

set ProjectRoot=C:\Users\Mark\Desktop\PirateClicker
set ProjectPureName=PirateClicker


rem Unreal path
set VersionSelector=%LauncherEpicGames%\Engine\Binaries\Win64\UnrealVersionSelector.exe
set RunUATPath=%EnginePath%\Engine\Build\BatchFiles\RunUAT.bat
set UBTRelativePath=%EnginePath%\Engine\Binaries\DotNET\UnrealBuildTool.exe
set EditorUE=%EnginePath%\Engine\Binaries\Win64\UE4Editor.exe

rem Path to Project
set ProjectName=%ProjectPureName%.uproject
set ProjectPath=%ProjectRoot%\%ProjectName%
