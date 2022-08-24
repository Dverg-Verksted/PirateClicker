@echo off

call "%~dp0\config.bat"

set dirsToRemove=Intermediate Saved DerivedDataCache Binaries .vs .idea Script
set filesToRemove=*.sln

for %%a in (%dirsToRemove%) do (
	echo %ProjectRoot%\%%a
    rmdir /S /Q %ProjectRoot%\%%a
)

for %%a in (%filesToRemove%) do (
	echo %ProjectRoot%\%%a
   del %ProjectRoot%\%%a
)

for /D %%a in ("%ProjectRoot%\Plugins\*") do (
	echo %%a\Intermediate
	echo %%a\Binaries
   rmdir /S /Q %%a\Intermediate
   rmdir /S /Q %%a\Binaries
)


"%UBTRelativePath%" -projectfiles -progress -project="%ProjectPath%"
"%UBTRelativePath%" DebugGame Win64 -Project="%ProjectPath%" -TargetType=Editor -Progress -NoEngineChanges -NoHotReloadFromIDE

PAUSE