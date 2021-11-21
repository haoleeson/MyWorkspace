#!/bin/bash

# STR="/dev/cu.usb-serial-14210"
STR=$(ls /dev/cu.usbserial-*)
RESULT=${STR##*-}
screen 
echo $RESULT