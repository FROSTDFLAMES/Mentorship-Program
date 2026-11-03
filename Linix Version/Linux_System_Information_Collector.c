#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>


// Manufacturer Name
int get_manufacturer(char *manufacturer, size_t size) {
    FILE *file = fopen("/sys/class/dmi/id/sys_vendor", "r");

    if (file == NULL) {
        perror("Failed to open manufacturer file.");
        return -1;
    }

    if (fgets(manufacturer, size, file) == NULL) {
        perror("Failed to read Manufacturer Name");
        fclose(file);
        return -1;
    }

    fclose(file);

    manufacturer[strcmp(manufacturer, "\n")] = '\0';

    return 0;
}


// Model Name
int get_product_name(char *model, size_t size) {
    FILE *file = fopen("/sys/class/dmi/id/product_version", "r");

    if (file == NULL) {
    perror("Failed to open Product File.");
    return -1;
    }

    if (fgets(model, size, file) == NULL) {
        perror("Failed to read Product Name ");
        fclose(file);
        return -1;
    }

    fclose(file);

    model[strcspn(model, "\n")] = '\0';

    return 0;
}


// Hostname
int get_host_name(char *hostname, size_t size) {
    if (gethostname(hostname, size) == -1) {
        perror("Failed to get Host Name.");
        return -1;
    }

    hostname[size -1] = '\0';

    return 0;
}


// Processor Architecture
int get_cpu_info(char *cpu, size_t size) {
    FILE *file = fopen("/proc/cpuinfo", "r");

    if (file == NULL) {
        perror("Failed to open CPU File.");
        return -1;
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "model name", 10) == 0) {
            char *value = strchr(line, ':');

            if (value != NULL) {
                value++;

                while (*value == ' ' || *value == '\t') {
                    value++;
                }

                snprintf(cpu, size, "%s", value);
                cpu[strcspn(cpu, "\n")] = '\0';

                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    return 0;
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

    if (get_host_name(hostname, sizeof(hostname)) == 0) {
        printf("Host Name: %s\n", hostname); 
    }

    // Processor Architecture Name
    char cpu[256];
    
    if(get_cpu_info(cpu, sizeof(cpu)) == 0) {
        printf("Processor Architecture: %s\n", cpu);
    }

    else {
        printf("Unable to retrieve CPU information.\n");
    }

    // Current Process ID
    pid_t pid = getpid();
    printf("Current Process ID: %d\n", pid);

    // System Uptime
    struct sysinfo info;

    if (sysinfo(&info) == -1) {
        perror("Failed to retrieve System infomation.");
        return 1;
    }

    long total = info.uptime;
    long h = total / 3600;
    long m = (total % 3600) / 60;
    long s = total % 60;

    printf("System Uptime: %ld hours, %02ld minutes, %02ld seconds\n", h, m , s);

    return 0;
}