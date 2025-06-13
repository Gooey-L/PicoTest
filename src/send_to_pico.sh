#!/bin/bash
PORT="/dev/ttyACM0"
LAST=""

while true; do
    SONG=$(playerctl metadata --format '{{title}}')
    if [[ "$SONG" != "$LAST" && -n "$SONG" ]]; then
        echo "$SONG" > "$PORT"
        LAST="$SONG"
    fi
    sleep 2
done
