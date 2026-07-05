@echo off
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0retarget_vcxproj.ps1" %*
echo Done.
pause
