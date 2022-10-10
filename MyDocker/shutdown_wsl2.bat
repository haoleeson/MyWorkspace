@echo off
setlocal enabledelayedexpansion

setLocal
:: set template var
set wslSysVersion=Debian

:: shutdown wsl distribution
wsl --shutdown %wslSysVersion%

echo  ====== shutdown WSL2 %wslSysVersion% success ======

wsl -l -v

endlocal

pause

