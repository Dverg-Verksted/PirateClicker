@echo off

call "%~dp0\config.bat"

set dirsToRemove=Intermediate Saved DerivedDataCache Binaries .vs .idea Script

echo Delete trash directory in project folder
for %%a in (%dirsToRemove%) do (
	echo %ProjectRoot%\%%a
    rmdir /S /Q %ProjectRoot%\%%a
)

echo Delete trash files
echo %ProjectRoot%\%ProjectPureName%.sln
del %ProjectRoot%\%ProjectPureName%.sln

echo Delete trash in Plugins
for /D %%a in ("%ProjectRoot%\Plugins\*") do (
	echo %%a\Intermediate
	echo %%a\Binaries
   rmdir /S /Q %%a\Intermediate
   rmdir /S /Q %%a\Binaries
)

"%UBTRelativePath%" -projectfiles -progress -project="%ProjectPath%"
"%UBTRelativePath%" Development Win64 -Project="%ProjectPath%" -TargetType=Editor -Progress -NoEngineChanges -NoHotReloadFromIDE

pause