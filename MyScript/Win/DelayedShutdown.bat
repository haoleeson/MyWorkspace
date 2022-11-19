@echo off
:: Set the shutdown delay time (unit: minutes)
set /a waitMinutes=5
set /a waitSeconds=%waitMinutes%*60

echo "This PC will shutdown after %waitMinutes% minutes ..."
shutdown -S -T %waitSeconds%
