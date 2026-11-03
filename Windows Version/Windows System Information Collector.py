import os

# Access system hardware details
import wmi

# Call function using Python for Windows API
import ctypes

# Time and Date
from datetime import timedelta

# Get's system uptime from the start of the boot
def windows_uptime():
    kernel32 = ctypes.windll.kernel32
    
    ms_since_boot = kernel32.GetTickCount64()
    
    uptime = timedelta(milliseconds = ms_since_boot)
    
    return str(uptime)

# Access system hardware and operating system details
kernel32 = ctypes.windll.kernel32

computer_name = ctypes.create_unicode_buffer(256)
size = ctypes.c_ulong(256)
kernel32.GetComputerNameW(computer_name, ctypes.byref(size))

c = wmi.WMI()
computer = c.Win32_ComputerSystem()[0]
processor = c.Win32_Processor()[0]
os_info = c.Win32_OperatingSystem()[0]

print(f"Manufacturer: {computer.Manufacturer}")
print(f"Model: {os_info.Caption}")
print(f"Hostname: {computer_name.value}")
print(f"Processor Architecture: {processor.Name.strip()}, {os.OSArchitecture}")
print(f"Current Proccess ID: {os.getpid()}")
print(f"System uptime: {windows_uptime}")