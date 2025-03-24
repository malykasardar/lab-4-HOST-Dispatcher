#include "types.h"
#include <stdio.h>
#include <stdlib.h>


extern Process process_list[MAX_PROCESSES];
extern int process_count;

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




/*********************************************************************
 * Group Number: 1
 *   - Abdullah Hanoosh, Student ID: 100749026
 *   - Malyka Sardar, Student ID: 100752640
 *   - Marwan Alam, Student ID: 100842087
 *   - Vidurshan Sribalasuhabiramam, Student ID: 100558257
 *********************************************************************/
