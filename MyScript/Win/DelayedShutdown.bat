@echo off
:: Set the shutdown delay time (unit: minutes)
set /a waitMinutes=5
set /a waitSeconds=%waitMinutes%*60

echo "This computer will shut down in %waitMinutes% minutes"
shutdown -S -T %waitSeconds%
