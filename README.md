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

## Compile project (Using compile-me.sh script)

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
