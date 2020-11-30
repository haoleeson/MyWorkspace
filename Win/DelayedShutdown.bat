@echo off
:: Set the shutdown delay time (unit: seconds)
set WAIT_TIME=300
echo "This computer will shut down in %WAIT_TIME% seconds"
shutdown -S -T %WAIT_TIME%
