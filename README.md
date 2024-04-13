# Pico Project
**Template project for developing software for Raspberry Pi Pico in C.**

![Automated CMake Build](https://github.com/KurtWagner23/pico-project/actions/workflows/build-ci.yml/badge.svg)
![Automated Testing](https://github.com/KurtWagner23/pico-project/actions/workflows/ci.yml/badge.svg) 

## Getting started/Prerequisites :rocket:

Additional documentation: [Official getting started PDF](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

- Prefered Editor/IDE is [Visual Studio Code](https://code.visualstudio.com/) but it works in every other Editor/IDE.

- Extensions you need to install in Visual Studio Code
  - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
  - [Microsoft C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
  - [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)

### Instructions for Linux :penguin:

- Dependencies to install for building and debugging:
```shell
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib ninja-build binutils-multiarch gdb-multiarch automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev pkg-config linux-tools-generic hwdata
```

### Windows and MacOS
- WSL:
For Windows it is recommended to use WSL and following Linux instructions.  
- Other:
Please refer to the [Official getting started PDF](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) from Raspberry Pi to get started with MacOS in chapter **9.1** and Windows in chapter **9.2**.  
- Debugging:
For debugging please follow the instructions in chapter **Appendix A** for Windows and MacOS. For **WSL** you can follow the instructions below.

## How To Build Template-Project :hammer:

### How To Connect RPI Pico and Sensors for Template-Project
- SDA: to GP16 on the right Pico
- SCL: to GP17 on the right Pico
- VCC: to 3V3 on the right Pico
- GDN: to GND on the right Pico
- Connnect both LIS3DHTR and DHT20 Sensor to I2C-Bus.
- Connect both Picos like this: (Pico on the left is Debug Probe)
![alt text](assets/PicoProbeWiring.png)
*Image Source: [Raspberry Pi]([source_link_here](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf))*

### Building Template in Visual Studio Code
  
![alt text](assets/VS-Code.png)

- :hammer_and_wrench: Selecting Preset Configuration
- :gear: Building selectedt configuration
- :arrow_forward: Executing selected target **(Only for Unit Testing Preset)**
- [main]: Selecting launch target **(Only for Unit Testing Preset)** 

### Building RPI Pico Executable From Command-Line
When building from the command-line you have to execute
```shell
cmake --preset "rp2040"
cmake --build --preset "rp2040"
```
or execute the build script
```shell
./build-rp2040.sh
``` 
in order to configure and compile the project executable for the Raspberry Pi Pico. 
 
### Flashing Raspberry Pi Pico (Without Debug Probe)
After compiling, the executable will be located in **build/rp2040/bin/** folder. 
Plugin the Pico into your PC while pressing and holding the BOOTSEL-Button. The Pico will be mounted as a external drive. Then you can drag-and-drop **main.uf2** located in the build-folder onto the mounted drive. 

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
After installing the dependencies from the sections above you can follow these steps on how to configure Debugging and automated flashing for the Raspberry Pi Pico. 

### Building Pico Probe 
You can either build Pico Probe for a second Raspberry Pi Pico yourself or use the precompiled binary in **PicoProbe-Precompiled** folder.  
- Flash your second Pico that will be used as PicoProbe with picoprobe_1.uf2
- Execute these commands in order:
```shell
cd ~
mkdir workspace
cd workspace
mkdir pico-build-tools 
cd pico-build-tools
git clone https://github.com/raspberrypi/openocd.git --branch rp2040-v0.12.0 --depth=1
cd openocd
./bootstrap
./configure
make -j4
sudo make install
sudo update-alternatives --install /usr/local/bin/usbip usbip $(command -v ls /usr/lib/linux-tools/*/usbip | tail -n1) 20
```
- Open a new terminal window and type: ```sudo openocd -f interface/cmsis-dap.cfg -c "adapter speed 5000" -f target/rp2040.cfg -s tcl```
  - This will start openocd and opens a port for gdb to listen to.
![alt text](assets/Pico-Debug.png)
- :arrow_forward: Start Debugging and Automatic Flashing
- **Important**: before starting to debug you have to build manually with the build-script or [build with VS-Code](#building-template-in-visual-studio-code)

## How To Use Template For Your Own Projects
- [ ] TODO: Add instructions on where to add libraries and how to implement Unit-Tests






