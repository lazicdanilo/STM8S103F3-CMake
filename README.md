# STM8S103F3-SDCC-CMake

## Prerequisites

### SPL download

First we need to download Standard Peripheral Libraries (SPL) from STs website. You can find the code [here](https://www.st.com/en/embedded-software/stsw-stm8069.html), keep in mind you will need to make an account and log in.
After download, move it into `spl` folder and unzip it.

### SPL patch

As SPL is not compatible with [SDCC](http://sdcc.sourceforge.net/) (compiler we want to use) we need to patch it using [STM8-SPL_SDCC_patch README](https://github.com/gicking/STM8-SPL_SDCC_patch#readme).
For instruction on how to do that checkout [STM8-SPL_SDCC_patch README](https://github.com/gicking/STM8-SPL_SDCC_patch#readme)

### Small Device C Compiler (SDCC)

```bash
# On Arch Linux
pacman -S sdcc

# On Ubuntu Linux
apt install sdcc
```

### stm8flash

```bash
# Install stm8flash from https://github.com/vdudouyt/stm8flash
pacman -S git libusb pkg-config

git clone git@github.com:vdudouyt/stm8flash.git /tmp/stm8flash && make -C /tmp/stm8flash && sudo make install -C /tmp/stm8flash
```

## Compile code uisng CMake and Make

The following commands can be used for compiling the code

```bash
mkdir build && cd build
cmake ..
make
```

Code can also be compiled using the `compile-me.sh` script

## Download to board using stm8flash

The following command can be used to download code to board

```bash
stm8flash -c stlinkv2 -p stm8s103f3 -s flash -w compiled_code.ihx
```

For download `compile-me.sh` script can be used as well. 

## compile-me.sh script usage

```bash
# Compile the project 
./compile-me.sh

# Recompile the project 
./compile-me.sh -r

# Compile and download to board 
./compile-me.sh -d

# Print help
./compile-me.sh -h
```
