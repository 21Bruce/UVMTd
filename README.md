# UVMTd
System Daemons for stress-testing UVM on OpenBSD. 

## Description
The intention for this project is to provide easy to run
daemons to test the behavior of the UVM system over time 
to catch bugs. There will be daemons both for black-box 
testing(i.e., holding large amounts of memory for varying
times and validating constantly), and for white-box testing
(i.e., using knowledge of UVM to force certain permutations
of the underlying vm_map structure).

## How to build
This project is intended to be run on OpenBSD, with
no other dependencies.
1. `git clone` this directory
2. run `make` in the cloned directory
3. run `./UVMTd` to spawn the two available daemons

## How to use 
At the moment, there is no UI to the program. All
files containing daemons are prefixed with `daemon_`.
The function needed to create them is found in
`spawn.c`. To display all running UVMTd daemons and information
about them, use the `dispd.sh` script, and to kill all daemons,
use the `killd.sh` script.
