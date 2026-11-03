# Allows communication between the clients and servers over a network.
import socket

# Processes and reads the system files to print the name of the device
import psutil
import subprocess

# Returns the machine hardware name
import platform

# Time and Date
import datetime


manufacturer = subprocess.check_output("cat /sys/class/dmi/id/sys_vendor", shell = True).decode().strip()
model = subprocess.check_output("cat /sys/class/dmi/id/product_version", shell = True, text = True).strip()

arch = platform.machine()

# Returns the Processor Specific Name
cpu = open("/proc/cpuinfo").read().split("model name")[1].split(":")[1].split("\n")[0]

# Get's system uptime from the start of the boot

def system_uptime():
    boot_time = psutil.boot_time()
    
    current_time = datetime.datetime.now().timestamp()
    
    uptime_seconds = current_time - boot_time
    
    return str(datetime.timedelta(seconds = int (uptime_seconds)))

print(f"Manufacturer: {manufacturer}")
print(f"Model: {model}")
print(f"Hostname: {socket.gethostname()}")
print(f"Processor Architecture:{cpu} {arch}")

print(f"Current Process ID: {psutil.Process().pid}")

print(f"System Uptime: {system_uptime()}")