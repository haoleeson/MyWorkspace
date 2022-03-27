#################################
#  Manual save /var/log/syslog  #
#################################

#!/usr/bin/env bash

NOW_TIME=$(date '+%Y-%m-%d--%H-%M-%S')
SAVE_FILE="/var/log/syslog--${NOW_TIME}.log"

# Backup log file /var/log/syslog
if [ -f /var/log/syslog ]; then
    sudo cp /var/log/syslog $SAVE_FILE
    sudo chmod a+r $SAVE_FILE
    echo "Success save the old syslog to $SAVE_FILE"
fi

# Manually delete /var/log/syslog
if [ -f /var/log/syslog ]; then
    sudo rm -f /var/log/syslog
fi

# Send HUP signal to Rsyslog
sudo /bin/kill -HUP $(cat /var/run/rsyslogd.pid)
