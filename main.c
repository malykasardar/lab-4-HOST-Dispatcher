#include <stdio.h>
#include "memory.h"  // Include the memory management module
#include "dispatcher.h"  // Include the dispatcher module

int main() {
    // Initialize memory pool
    initMemory();
    
    Dispatcher dispatcher;
    dispatcher.queue = NULL;

    // Example: Adding processes to the dispatcher
    addProcess(&dispatcher, createProcess(1, 1, 10));  // Process 1
    addProcess(&dispatcher, createProcess(2, 2, 5));   // Process 2
    addProcess(&dispatcher, createProcess(3, 1, 8));   // Process 3

    // Select scheduler mode
    int choice;
    printf("Choose Scheduler Mode:\n1. FCFS\n2. Round Robin\n3. User Feedback\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS(&dispatcher);
            break;
        case 2:
            roundRobin(&dispatcher);
            break;
        case 3:
            userFeedback(&dispatcher);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;
}
