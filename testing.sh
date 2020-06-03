#!bin/bash

# Author: Erich Woo & Spencer Grimm
# Date: 3 June 2020
#

make clean
make

# Unit Testing
make unit

# Fuzztesting
./fuzzsudo 1000
