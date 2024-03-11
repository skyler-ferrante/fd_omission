#!/bin/bash
# requires root
gcc -o show_open show_open.c
gcc -o fd_omit fd_omit.c
# Be careful, the binary this creates is not secure
sudo chown root show_open
sudo chmod u+s show_open
