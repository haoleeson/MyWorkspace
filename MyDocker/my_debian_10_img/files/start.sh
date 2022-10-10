#!/bin/bash
set -e

supervisorctl start rsyslogd
supervisorctl start sshd

echo 'start.sh done.'
