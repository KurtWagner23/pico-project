import os
import sys
import time
import glob
import shutil
import serial
import platform
from serial.tools import list_ports

def detect_serial_port():
    print("Detecting serial port...")
    ports = list_ports.comports()
    for port in ports:
        try:
            with serial.Serial(port.device) as ser:
                ser.baudrate = 1200
                ser.close()
                print(f"Detected Pico on {port.device}")
                return port.device
        except serial.SerialException:
            continue
    print("No Pico detected on any serial port.")
    sys.exit(1)

def wait_for_device(device, timeout=15):
    print("waiting for pico to mount")
    count = 0
    while not os.path.exists(device):
        time.sleep(2)
        count += 1
        print(".")
        if count >= 2 * timeout:
            print(f"No device found on serial port {device} - Aborting process.")
            sys.exit(1)

def delete_mass_storage_relics():
    print("deleted mass storage relics (if existing):")
    if platform.system() == 'Windows':
        mount_points = [drive for drive in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' if os.path.exists(f'{drive}:\\RPI-RP2')]
        for mount_point in mount_points:
            shutil.rmtree(f'{mount_point}:\\RPI-RP2')
            print(f"Deleted {mount_point}:\\RPI-RP2")
    elif platform.system() == 'Darwin':  # macOS
        mount_points = glob.glob('/Volumes/RPI-RP*')
        for mount_point in mount_points:
            shutil.rmtree(mount_point)
            print(f"Deleted {mount_point}")
    else:  # Linux
        mount_points = glob.glob(f"/media/{os.getenv('USER')}/RPI-RP*")
        for mount_point in mount_points:
            shutil.rmtree(mount_point)
            print(f"Deleted {mount_point}")

def reset_pico(device):
    print("resetting pico")
    try:
        with serial.Serial(device) as ser:
            ser.baudrate = 1200
            ser.close()
    except serial.SerialException as e:
        print(f"Resetted Pico")
        sys.exit(1)

def find_mount_point():
    if platform.system() == 'Windows':
        mount_points = [drive for drive in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' if os.path.exists(f'{drive}:\\RPI-RP2')]
        if mount_points:
            return f"{mount_points[0]}:\\RPI-RP2"
    elif platform.system() == 'Darwin':  # macOS
        mount_points = glob.glob('/Volumes/RPI-RP*')
        if mount_points:
            return mount_points[0]
    else:  # Linux
        mount_points = glob.glob(f"/media/{os.getenv('USER')}/RPI-RP*")
        if mount_points:
            return mount_points[0]
    return None

def wait_for_mount(timeout=15):
    count = 0
    while True:
        time.sleep(0.5)
        mount_point = find_mount_point()
        if mount_point:
            return mount_point
        print(".")
        count += 1
        if count >= 2 * timeout:
            print("pico did not reboot - try again!")
            sys.exit(1)

def copy_flash_file(mount_point, binary_path):
    print("copy flash-file to pico...")
    try:
        shutil.copy(binary_path, mount_point)
        print(f"Copied {binary_path} to {mount_point}")
    except shutil.Error as e:
        print(f"Failed to copy flash file: {e}")
        sys.exit(1)

def check_flash_success(mount_point, timeout=5):
    count = 0
    while os.path.exists(mount_point):
        time.sleep(0.5)
        print(".")
        count += 1
        if count >= 2 * timeout:
            print("pico was reset but could not be flashed - please drag and drop .uf2-file manually!")
            sys.exit(1)

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <binary_path>")
        sys.exit(1)

    binary_path = sys.argv[1]

    if not os.path.isfile(binary_path):
        print(f"Binary file {binary_path} does not exist.")
        sys.exit(1)

    device = detect_serial_port()

    print(device)

    #wait_for_device(device)
    #delete_mass_storage_relics()
    reset_pico(device)
    mount_point = wait_for_mount()
    time.sleep(0.5)  # give pico some time to mount fully
    copy_flash_file(mount_point, binary_path)
    check_flash_success(mount_point)

    print("flash successful - black magic happened ~\\(o.O~\\)")

if __name__ == "__main__":
    main()
