#include <windows.h>
#include <stdio.h>
#include <string.h>


// Manufacturer Name
int get_manufacturer(char *manufacturer, DWORD size) {
    HKEY hKey;
    DWORD type;
    DWORD result_size = size;

    LONG result = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey
    );

    if (result != ERROR_SUCCES) {
        printf("Failed to open Registry Key: %ld\n", result);
        return -1
    }

    result = RegQueryValueExA(hKey, "SystemManufacturer", NULL, &type, (LPBYTE)manufacturer, &result_size);

    RegCloseKey(hKey);

    if (result != ERROR_SUCCESS || type != REG_SZ) {
        printf("Failed to retrieve Manufacturer Name\n");
        return -1;
    }

    manufacturer[size - 1] = '\0';
    return 0;

}

// Model Name
int get_model(char *model, DWORD size) {
    HKEY hKey;
    DWORD type;
    DWORD result_size = size;

    LONG result = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey
    );

    if (result != ERROR_SUCCES) {
        printf("Failed to open Registry Key: %ld\n", result);
        return -1
    }

    result = RegQueryValueExA(hKey, "SystemVersion", NULL, &type, (LPBYTE)model, &result_size);

    RegCloseKey(hKey);

    if (result != ERROR_SUCCESS || type != REG_SZ) {
        printf("Failed to retrieve Model Name\n");
        return -1;
    }

    model[size - 1] = '\0';
    return 0;
}

// CPU Information
int get_cpu(char *cpu, DWORD size) {
    HKEY hKey;
    DWORD type;
    DWORD result_size = size;

    LONG result = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey
    );

    if (result != ERROR_SUCCES) {
        printf("Failed to open Registry Key: %ld\n", result);
        return -1
    }

    result = RegQueryValueExA(hKey, "SystemVersion", NULL, &type, (LPBYTE)cpu, &result_size);

    RegCloseKey(hKey);

    if (result != ERROR_SUCCESS || type != REG_SZ) {
        printf("Failed to retrieve CPU information\n");
        return -1;
    }

    cpu[size - 1] = '\0';
    return 0;
}

// Current Process ID
DWORD get_current_process_id(void) {
    return GetCurrntProcessId();
}

int main(void) {
    // Manufacturer Name
    char manufacturer[128];

    if (get_manufacturer(manufacturer, sizeof(manufacturer)) == 0) {
        printf("Manufacturer: %s", manufacturer);
    }

    // Model Name
    char model[128];

    if (get_product_name(model, sizeof(model)) == 0) {
        printf("Model: %s\n", model);
    }

    else {
        perror("Failed to get Model Name");
    }

    // Host Name
    char hostname[256];
    DWORD size = sizeof(hostname);

    if (GetComputerNameA(hostname, &size)) {
        printf("Host Name: %s\n", hostname);
    }
    else {
        printf("Failed to get Host Name.\n");
    }

    // CPU Name
    char cpu[128];

    if (get_manufacturer(cpu, sizeof(cpu)) == 0) {
        printf("Processor Architecture: %s", cpu);
    }

    // Current Process ID
    DWORD pid = get_current_process_id();
    printf("Current Process ID: %lu\n", (unsigned long)pid);

    // Current Uptime
    ULONGLONG ticks = GetTickCount64();

    ULONGLONG hours = ticks / (1000 * 60 * 60);
    ULONGLONG minutes = (ticks % (1000 * 60 * 60)) / (1000 * 60 * 60);
    ULONGLONG seconds = (ticks % (1000 * 60)) / 1000;

    printf("Current Uptime: %llu hours, %llu minutes, %llu seconds\n", hours, minutes, seconds);

    return 0;
}