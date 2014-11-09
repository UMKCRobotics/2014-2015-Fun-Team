#!/bin/bash

# Made by Caleb Chase.
# Purpose: Create a connection over usb for SSH access and bridge to the internet as well.

# Update these depending on what interfaces your computer uses.
INET_IFACE=tun0
BB_IFACE=enp0s29u1u2

# Enable DHCP client if not already -- may not be necessary for you.
dhcp_procs=`ps aux | grep dchp`
if [[ $dhcp_procs != *$BB_IFACE* ]]; then
    dhcpcd $BB_IFACE
fi

# Enable internet forwarding.
echo 1 > /proc/sys/net/ipv4/ip_forward
# Setup iptables rules to bridge beaglebone to internet.
iptables -t nat -A POSTROUTING -o $INET_IFACE -j MASQUERADE
iptables -A FORWARD -i $BB_IFACE -o $INET_IFACE -j ACCEPT
iptables -A FORWARD -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT

# Update beaglebone config.
route="ip route add default via 192.168.7.1"
dns="echo nameserver 8.8.8.8 > /etc/resolv.conf"
set_time="ntpdate pool.ntp.org"
ssh root@192.168.7.2 "$route;$dns;$set_time"
