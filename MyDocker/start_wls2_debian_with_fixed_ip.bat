@echo off
setlocal enabledelayedexpansion

setLocal
:: set template var
set wslSysVersion=Debian
set IpPrefix=172.24.32
set wslHostIp=172.24.32.181
set vEthernetWslIp=172.24.32.1

:: Start wsl with target IP
wsl --shutdown %wslSysVersion%
:: start ssh
wsl -u root -d %wslSysVersion% service ssh start
:: start docker
wsl -u root -d %wslSysVersion% service docker start
echo wsl -u root ip addr add %wslHostIp%/24 broadcast %IpPrefix%.0 dev eth0 label eth0:1
wsl -u root ip addr add %wslHostIp%/24 broadcast %IpPrefix%.0 dev eth0 label eth0:1
echo set WSL2 %wslSysVersion% ip success: %wslHostIp%

:: Add sub net of vEthernet with same IP prefix
ipconfig | findstr %vEthernetWslIp% > nul
if !errorlevel! equ 0 (
    echo windows ip has been setted %vEthernetWslIp%
) else (
    echo netsh interface ip add address "vEthernet (WSL)" %vEthernetWslIp% 255.255.255.0
    netsh interface ip add address "vEthernet (WSL)" %vEthernetWslIp% 255.255.255.0
    echo set windows ip success: %vEthernetWslIp%
)

endlocal

pause