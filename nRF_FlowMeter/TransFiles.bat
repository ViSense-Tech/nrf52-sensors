@echo off
set "sourceFolder=%cd%\ti"
set "destinationFolder=C:\"

xcopy /E /I "%sourceFolder%" "%destinationFolder%"

echo Folder copied successfully to C: drive.

pause
