#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100
#define MEMORY_SIZE 1024 // Total available memory in MB
#define TIME_QUANTUM 1    // Time quantum for user processes

typedef struct {
    int arrival_time;
    int priority;
    int processor_time;
    int memory;
    int printers;
    int scanners;
    int modems;
    int cds;
    int process_id;
} Process;

Process process_list[MAX_PROCESSES];
int process_count = 0;

void read_dispatch_list(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open dispatch list file.\n");
        exit(1);
    }
    
    while (fscanf(file, "%d, %d, %d, %d, %d, %d, %d, %d", 
                  &process_list[process_count].arrival_time, 
                  &process_list[process_count].priority, 
                  &process_list[process_count].processor_time, 
                  &process_list[process_count].memory, 
                  &process_list[process_count].printers, 
                  &process_list[process_count].scanners, 
                  &process_list[process_count].modems, 
                  &process_list[process_count].cds) == 8) {
        process_list[process_count].process_id = process_count + 1;
        process_count++;
    }
    fclose(file);
}

void execute_dispatcher() {
    printf("\nExecuting Processes:\n");
    for (int i = 0; i < process_count; i++) {
        printf("Running Process: ID=%d, Priority=%d, Time Remaining=%d sec, Memory=%d MB\n", 
               process_list[i].process_id, process_list[i].priority, 
               process_list[i].processor_time, process_list[i].memory);
    }
}

int main() {
    char filename[100];
    printf("Enter dispatch list filename: ");
    scanf("%s", filename);
    
    read_dispatch_list(filename);
    execute_dispatcher();
    
    return 0;
}
