# Dieharder Experiments

This directory contains all the source files needed to reproduce the dieharder 
results that quantify the quality of a random number generation (RNG) scheme. The 
files and workflow described here can be used to recreate the results shown in 
Figure 5. 

## Requirements

### RDSEED

The quality of a RNG scheme is quanitfied by the degree to which the RNG must be 
reseeded to obtain results similar to `rdrand` instruction. RNGs from this study 
use `rdseed` to provide a high quality seed, and the frequency of reseeding can 
be set by a command line argument. Thus, the hardware system that runs the 
applications contained in this directory must support the `rdseed` instruction. 
For convenience, a simple C program is provided that checks the existence of 
support for this instruction. It can compile and run with the following in this 
directory:

```
make
./check_rdseed.o
```

Which, if successful, will display the message:

```
RDSEED is supported on this CPU.
```

### Dieharder

Beyond having native support for the `rdseed` instruction, the `dieharder` 
package must be installed. In this work, version 3.31.1 of dieharder was used.
Diharder can be installed with `apt` on Ubuntu:

```
sudo apt install dieharder
```

## Getting Started

First ensure that all needed software dependencies are installed:

```
sudo apt update
sudo apt install build-essential dieharder
```

## Run Dieharder on Target RNG

Navigate into a RNG directory. For example, to evaluate the Mersenne Twister 
RNG scheme, perform the following:

```
cd mersenne_twister/
make clean 
make
make 
```

