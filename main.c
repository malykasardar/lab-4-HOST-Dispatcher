#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100
#define MEMORY_SIZE 1024 // Total available memory in MB
#define TIME_SLICE 5      // Time quantum for round robin scheduling

// Process structure
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

// Dispatcher structure
typedef struct {
    Process* queue;
} Dispatcher;

// Function prototypes
void loadProcessesFromFile(Dispatcher* dispatcher, const char* fileName);
void executeProcesses(Dispatcher* dispatcher);
void FCFS(Dispatcher* dispatcher);       // First Come First Served
void roundRobin(Dispatcher* dispatcher); // Round Robin
void userFeedback(Dispatcher* dispatcher); // User Feedback (feedback based scheduling)

// Function to load processes from a file
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

// Execute processes for all scheduling methods
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

// FCFS Scheduler (First Come First Served)
void FCFS(Dispatcher* dispatcher) {
    printf("\nExecuting Processes using FCFS:\n");
    for (int i = 0; i < process_count; i++) {
        printf("Executing Process ID: %d, Priority: %d, Processor Time: %d\n", 
               process_list[i].process_id, 
               process_list[i].priority, 
               process_list[i].processor_time);
    }
}

// Round Robin Scheduler
void roundRobin(Dispatcher* dispatcher) {
    Process* current = process_list;
    printf("\nExecuting Processes using Round Robin:\n");
    while (1) {
        int completed = 1; // Flag to check if all processes are completed
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

// User Feedback Scheduler (adjusts priority based on feedback)
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

            // Adjust priority if process is taking longer
            if (process_list[i].processor_time > 0) {
                process_list[i].priority--; // Reduce priority if not completed
            }
        }
    }
}

int main() {
    char fileName[100];
    printf("Enter the file name for the dispatcher list: ");
    scanf("%s", fileName);

    Dispatcher dispatcher;
    dispatcher.queue = NULL;  // Initialize the queue

    // Load processes from the file
    loadProcessesFromFile(&dispatcher, fileName);
    
    // Execute dispatcher based on the selected scheduler mode
    executeProcesses(&dispatcher);
    
    return 0;
}
