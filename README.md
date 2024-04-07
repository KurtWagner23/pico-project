# Pico Project
**Template project for developing software for Raspberry Pi Pico in C.**

![Automated CMake Build](https://github.com/KurtWagner23/pico-project/actions/workflows/build-ci.yml/badge.svg)
![Auoomated Testing](https://github.com/KurtWagner23/pico-project/actions/workflows/ci.yml/badge.svg) 

## Getting started/Prerequisites :rocket:

Additional documentation: [Official getting started PDF](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

- Prefered Editor/IDE is [Visual Studio Code](https://code.visualstudio.com/) but it works in every other Editor/IDE.

- Extensions you need to install in Visual Studio Code
  - CMake Tools
  - Microsoft C/C++
  - Cortex-Debug

### Instructions for Linux :penguin:

- Dependencies that you will need:
```shell
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib ninja-build binutils-multiarch gdb-multiarch automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev pkg-config linux-tools-generic hwdata
```

### Windows
- [ ] TODO: Adding instructions

### Mac0S
- [ ] TODO: Adding instructions


## How To Build Template-Project :hammer:

### How To Connect RPI Pico and Connect Sensors for Template-Project
- [ ] TODO: Here a picture of connections

### Building in Visual Studio Code
In Visual Studio Code when you open the cloned project folder, CMake Tools Extension should automatically detect all CMake configurations in CMakePresets.json and configure everything for you.  
You can choose between ***Unit-Testing***  and ***build-rp2040*** configuration on the status bar at the bottom. By clicking on the **Gear-Symbol** you can compile selected configuration.  
For ***Unit-Testing*** you can also click on the **Arrow-Symbol** to execute the Tests in the command-line.  
**Note:** This is not working for the ***build-rp2040*** configuration because we are compiling for the Raspberry Pi Pico and cannot execute the binary on our Host-Machine!!!


### Building RPI Pico Executable From Command-Line
When building from the command-line you have to execute
```shell
cmake --preset "rp2040"
cmake --build --preset "rp2040"
```
or
```shell
./build-rp2040.sh
``` 
in order to configure and compile the project executable for the Raspberry Pi Pico. 
 
### Flashing Raspberry Pi Pico
After compiling the executable will be located in **build/rp2040/bin/**. 
Plugin the Pico into your PC while pressing and holding the BOOTSEL-Button. Then the PICO will be mounted like a USB-Drive. Then you drag-and-drop **main.uf2** onto the mounted drive. 

### Unit-Testing From Command-Line
When you want to execute the Unit-Tests from command-line you have to execute
```shell
cmake --preset "test"
cmake --build --preset "test"
cd build/test
ctest -VV
```
or 
```shell
./build-tests.sh
cd build/test
ctest -VV
```
The test-runner.sh script is used in GitHub Action Continous-Integration-Pipeline but you can also use this script to compile and execute the Unit-Tests.

## How To Debug With Pico Probe
- [ ] TODO: Add debugging instructions and picture of connections


## How To Use Template For Your Own Projects
- [ ] TODO: Add instructions on where to add libraries and how to implement Unit-Tests






