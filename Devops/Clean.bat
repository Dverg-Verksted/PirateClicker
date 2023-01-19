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
