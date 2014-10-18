#!/bin/bash

# Written by Caleb Chase
# Automatically copy via rsync and build remotely with scons on modification.

LOCAL_DIR="/home/caleb/sync/code/2014-2015-Fun-Team"
REMOTE_DIR="/home/root/caleb/"
IP="root@192.168.2.202"

# TODO: add inotify loop
rsync -e "sshpass -p '' ssh" -avz $LOCAL_DIR $IP:$REMOTE_DIR
sshpass -p '' ssh $IP "cd /home/root/caleb/2014-2015-Fun-Team && scons"
