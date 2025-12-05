#!/bin/bash

sudo docker run -it -v "$(pwd)":/freedom --user $(id -u):$(id -g) freedom $@