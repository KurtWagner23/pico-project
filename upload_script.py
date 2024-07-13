import os
import time
import sys
import subprocess

def run_command(command):
    if sys.platform.startswith('win'):
        subprocess.run(command, creationflags=subprocess.CREATE_NO_WINDOW, check=True)
    else:
        subprocess.run(command, shell=True, check=True)

def main():
    if sys.platform.startswith('win'):
        run_command(['picotool', 'reboot', '-f', '-u'])
        time.sleep(0.5)
        run_command(['picotool', 'load', sys.argv[1]])
        time.sleep(0.5)
        run_command(['picotool', 'reboot', '-f'])
    else:
        run_command(f'picotool load -f {sys.argv[1]}')

if __name__ == "__main__":
    main()
