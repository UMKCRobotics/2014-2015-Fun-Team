#!/bin/bash

# Written by Caleb Chase
# Automatically copy via rsync on modification of files.

LOCAL_DIR="/home/caleb/sync/code/2014-2015-Fun-Team"
REMOTE_DIR="/root/caleb/"
IP="root@192.168.7.2"

inotifywait --monitor --recursive --event modify,close_write,move,create,delete $LOCAL_DIR |
    while read file; do
        echo "Copying..."
        rsync -av $LOCAL_DIR $IP:$REMOTE_DIR
        ssh $IP "cd $REMOTE_DIR/2014-2015-Fun-Team"
        echo "Done"
        echo ""
    done
