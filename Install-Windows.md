# Install Instructions for Windows
## Native: 
Please download and install [Pico Setup for Windows](https://github.com/raspberrypi/pico-setup-windows/releases/latest/download/pico-setup-windows-x64-standalone.exe). All needed tools are included.
Please install [Zadig](https://zadig.akeo.ie/) and install the **libusb-win32** driver for Picotool to work correctly.

### OPenOCD

- Please change this line to settings.json inside .vscode folder.
```json
  "cortex-debug.openocdPath": "<PATH TO OPENOCD.EXE>"
```
- Change the Path to where you installed OpenOCD with **Pico Setup for Windows**.

## WSL:
When you want to use WSL then you can follow the Linux Instructions for installing.