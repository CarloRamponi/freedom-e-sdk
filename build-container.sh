#!/bin/bash

echo "Building Freedom E SDK Docker container..."
echo "This may take a while..."

(sleep 10 && echo && echo "Still working... please be patient.") &
PID=$!
trap "kill $PID" EXIT

(sleep 60 && echo && echo "Told you so!") &
PID2=$!
trap "kill $PID2" EXIT

sudo docker build -t freedom .