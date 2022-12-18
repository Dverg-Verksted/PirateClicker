@echo off

call "%~dp0\config.bat"

"%UBTRelativePath%" -projectfiles -progress -project="%ProjectPath%"
"%UBTRelativePath%" Development Win64 -Project="%ProjectPath%" -TargetType=Editor -Progress -NoEngineChanges -NoHotReloadFromIDE

pause