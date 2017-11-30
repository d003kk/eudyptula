#!/bin/bash
insmod hello-1.ko
echo "045e 0730" > /sys/bus/usb/drivers/hello/new_id
echo -n "4-2:1.1" > /sys/bus/usb/drivers/usbhid/unbind
echo -n "4-2:1.1" > /sys/bus/usb/drivers/hello/bind
echo -n "4-2:1.0" > /sys/bus/usb/drivers/usbhid/unbind
echo -n "4-2:1.0" > /sys/bus/usb/drivers/hello/bind
rmmod usbhid
echo "blacklist usbhid" >> /etc/modprobe.d/blacklist.conf 
