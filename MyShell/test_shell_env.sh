#!/usr/bin/env bash

export ENV_ORCHAGENT_F=$(redis-cli -n 3 HGET "orchagent:orchagent" "FACILITY")
export ENV_ORCHAGENT_L=$(redis-cli -n 3 HGET "orchagent:orchagent" "LOGLEVEL")

export ENV_TRANSMGRD_F=$(redis-cli -n 3 HGET "transmgrd:transmgrd" "FACILITY")
export ENV_TRANSMGRD_L=$(redis-cli -n 3 HGET "transmgrd:transmgrd" "LOGLEVEL")

# echo ">>>> 1.sh env:"
# env

# sh 2.sh

# Save to file
cat /dev/null > /var/log/logctl_val2.conf
echo "ENV_ORCHAGENT_F=${ENV_ORCHAGENT_F}" >> /var/log/logctl_val2.conf
echo "ENV_ORCHAGENT_L=${ENV_ORCHAGENT_L}" >> /var/log/logctl_val2.conf
echo "ENV_TRANSMGRD_F=${ENV_TRANSMGRD_F}" >> /var/log/logctl_val2.conf
echo "ENV_TRANSMGRD_L=${ENV_TRANSMGRD_L}" >> /var/log/logctl_val2.conf

redis-cli -n 3 "bgp#bgpcfgd" "FACILITY" "LOCAL3"
redis-cli -n 3 "bgp#bgpcfgd" "LOGLEVEL" "ERROR"