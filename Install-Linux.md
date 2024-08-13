# Install Instructions for Linux

## Dependencies to install for building and debugging:
```shell
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib ninja-build binutils-multiarch gdb-multiarch automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev pkg-config linux-tools-generic hwdata clang-tidy clang-format
```

## Picotool
Repository: [Picotool GitHub](https://github.com/raspberrypi/picotool).  
Install steps **(Only needed for Linux)**:
- Clone Repository
- Clone Pico-SDK Repository in the same directory
- ```cmake -B build -S . -DPICO_SDK_PATH=../pico-sdk```
- ```cd build && sudo make install ```
- ```cd .. && sudo cp udev/99-picotool.rules /etc/udev/rules.d/```
- Then you can use Picotool without sudo

## Pico-Probe

You can either build Pico Probe for a second Raspberry Pi Pico yourself or use the precompiled binary in **PicoProbe-Precompiled** folder.  
- Flash your second Pico that will be used as PicoProbe with picoprobe_1.uf2
### OpenOCD
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