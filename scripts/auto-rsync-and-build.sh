#!/bin/bash

# Written by Caleb Chase
# Automatically copy via rsync on modification of files.

LOCAL_DIR="/home/caleb/sync/code/2014-2015-Fun-Team"
REMOTE_DIR="/root/caleb/"
IP="root@192.168.7.2"

while inotifywait --recursive --event modify,close_write,move,create,delete $LOCAL_DIR; do
        echo "Copying..."
        rsync -av $LOCAL_DIR $IP:$REMOTE_DIR
        echo "Done"
        echo ""
done
