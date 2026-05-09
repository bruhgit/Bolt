@echo off
setlocal

set VS2026="%ProgramFiles%\Microsoft Visual Studio\18\Insiders\VC\Auxiliary\Build\vcvars64.bat"

if exist %VS2026% (
    call %VS2026%
    goto ready
)

echo VS 2026 Insiders vcvars64.bat not found
echo Yol: %VS2026%
pause
exit /b

:ready
echo =====================================
echo VS 2026 x64 MSVC
echo cl.exe ready
echo =====================================

cmd /k