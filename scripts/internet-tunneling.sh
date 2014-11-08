#!/bin/bash

# Made by Caleb Chase.
# Purpose: Create a connection over ethernet for SSH access and bridge to the internet as well.
# This only works for me right now.

# Local access.
ip addr add 192.168.2.10/24 dev enp2s0
ip link set enp2s0 up
systemctl start dhcpd4

# Bridge beaglebone to internet.
iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE
iptables -A FORWARD -i enp2s0 -o tun0 -j ACCEPT
iptables -A FORWARD -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT

# TODO: need to add default route ON BEAGLEBONE?
# ip route add efault via 192.168.2.1 dev eth0
