#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Process* queue;
} Dispatcher;

Process process_list[MAX_PROCESSES];
int process_count = 0;

void loadProcessesFromFile(Dispatcher* dispatcher, const char* fileName);
void executeProcesses(Dispatcher* dispatcher);
void FCFS(Dispatcher* dispatcher);
void roundRobin(Dispatcher* dispatcher);
void userFeedback(Dispatcher* dispatcher);

void loadProcessesFromFile(Dispatcher* dispatcher, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Error: Could not open dispatch list file.\n");
        exit(1);
    }

    int arrival_time, priority, processor_time, memory, printers, scanners, modems, cds;
    while (fscanf(file, "%d, %d, %d, %d, %d, %d, %d, %d", 
                  &arrival_time, 
                  &priority, 
                  &processor_time, 
                  &memory, 
                  &printers, 
                  &scanners, 
                  &modems, 
                  &cds) == 8) {
        Process process = {arrival_time, priority, processor_time, memory, printers, scanners, modems, cds, process_count + 1};
        process_list[process_count++] = process;
    }

    fclose(file);
}

void executeProcesses(Dispatcher* dispatcher) {
    int choice;
    printf("Choose Scheduler Mode:\n1. FCFS\n2. Round Robin\n3. User Feedback\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS(dispatcher);
            break;
        case 2:
            roundRobin(dispatcher);
            break;
        case 3:
            userFeedback(dispatcher);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}

void FCFS(Dispatcher* dispatcher) {
    printf("\nExecuting Processes using FCFS:\n");
    for (int i = 0; i < process_count; i++) {
        printf("Executing Process ID: %d, Priority: %d, Processor Time: %d\n", 
               process_list[i].process_id, 
               process_list[i].priority, 
               process_list[i].processor_time);
    }
}

void roundRobin(Dispatcher* dispatcher) {
    Process* current = process_list;
    printf("\nExecuting Processes using Round Robin:\n");
    while (1) {
        int completed = 1;
        for (int i = 0; i < process_count; i++) {
            if (process_list[i].processor_time > 0) {
                completed = 0;
                int timeToExecute = (process_list[i].processor_time > TIME_SLICE) ? TIME_SLICE : process_list[i].processor_time;
                printf("Executing Process ID: %d for %d units\n", process_list[i].process_id, timeToExecute);
                process_list[i].processor_time -= timeToExecute;

                if (process_list[i].processor_time == 0) {
                    printf("Process %d completed.\n", process_list[i].process_id);
                }
            }
        }
        if (completed) {
            break;
        }
    }
}

void userFeedback(Dispatcher* dispatcher) {
    printf("\nExecuting Processes using User Feedback Scheduler:\n");
    for (int i = 0; i < process_count; i++) {
        if (process_list[i].processor_time > 0) {
            int timeToExecute = (process_list[i].processor_time > TIME_SLICE) ? TIME_SLICE : process_list[i].processor_time;
            printf("Executing Process ID: %d for %d units\n", process_list[i].process_id, timeToExecute);
            process_list[i].processor_time -= timeToExecute;

            if (process_list[i].processor_time == 0) {
                printf("Process %d completed.\n", process_list[i].process_id);
            }

            if (process_list[i].processor_time > 0) {
                process_list[i].priority--;
            }
        }
    }
}

int main() {
    char fileName[100];
    printf("Enter the file name for the dispatcher list: ");
    scanf("%s", fileName);

    Dispatcher dispatcher;
    dispatcher.queue = NULL;

    loadProcessesFromFile(&dispatcher, fileName);
    
    executeProcesses(&dispatcher);
    
    return 0;
}

