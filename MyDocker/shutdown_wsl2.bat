@echo off
setlocal enabledelayedexpansion

setLocal
:: set template var
set wslSysVersion=Debian

:: stop all containers
docker ps -q | % { docker stop $_ }

:: Sleep 3 s
timeout /t 3 /nobreak

:: shutdown wsl distribution
wsl --shutdown %wslSysVersion%

echo  ====== shutdown WSL2 %wslSysVersion% success ======

wsl -l -v

endlocal

pause

