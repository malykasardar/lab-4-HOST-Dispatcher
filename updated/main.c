/*********************************************************************
 * Group Number: 1
 *   - Abdullah Hanoosh, Student ID: 100749026
 *   - Malyka Sardar, Student ID: 100752640
 *   - Marwan Alam, Student ID: 100842087
 *   - Vidurshan Sribalasuhabiramam, Student ID: 100558257
 *********************************************************************/
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

Process process_list[MAX_PROCESSES];
int process_count = 0;

int main() {
    char fileName[100];
    printf("Enter the file name for the dispatcher list: ");
    scanf("%s", fileName);

    loadProcessesFromFile(fileName);
    executeProcesses();

    return 0;
}

void loadProcessesFromFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    int arrival_time, priority, processor_time, memory, printers, scanners, modems, cds, is_real_time;
    while (fscanf(file, "%d, %d, %d, %d, %d, %d, %d, %d, %d",
                  &arrival_time, &priority, &processor_time, &memory, &printers, &scanners, &modems, &cds, &is_real_time) == 9) {
        Process process = {arrival_time, priority, processor_time, memory, printers, scanners, modems, cds, process_count + 1, is_real_time, 1};
        process_list[process_count++] = process;
    }
    fclose(file);
}

void executeProcesses() {
    init_resources();
    int choice;
    printf("Choose Scheduler Mode:\n1. FCFS\n2. Round Robin\n3. User Feedback\n4. Mixed Scheduler\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS();
            break;
        case 2:
            roundRobin();
            break;
        case 3:
            userFeedback();
            break;
        case 4:
            mixedScheduler();
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
    printProcessStatus();
}

void FCFS() {
    printf("\nExecuting Processes using FCFS:\n");
    for (int i = 0; i < process_count; i++) {
        if (process_list[i].active && (process_list[i].is_real_time || process_list[i].priority > 5) && allocate_resources(&process_list[i])) {
            printf("Process ID %d (Priority: %d, Real-Time: %d) completes using FCFS.\n", process_list[i].process_id, process_list[i].priority, process_list[i].is_real_time);
            process_list[i].processor_time = 0;
            process_list[i].active = 0;
            release_resources(&process_list[i]);
        }
    }
}

void roundRobin() {
    printf("\nExecuting Processes using Round Robin:\n");
    int all_done;
    do {
        all_done = 1;
        for (int i = 0; i < process_count; i++) {
            if (process_list[i].active && process_list[i].processor_time > 0 && allocate_resources(&process_list[i])) {
                printf("Running Process ID %d for %d units in Round Robin.\n", process_list[i].process_id, TIME_SLICE);
                process_list[i].processor_time -= TIME_SLICE;
                if (process_list[i].processor_time > 0) {
                    all_done = 0;
                } else {
                    printf("Process ID %d completes execution in Round Robin.\n", process_list[i].process_id);
                    process_list[i].active = 0;
                }
                release_resources(&process_list[i]);
            }
        }
    } while (!all_done);
}

void userFeedback() {
    printf("\nExecuting Processes using User Feedback Scheduler:\n");
    int all_done;
    do {
        all_done = 1;
        for (int i = 0; i < process_count; i++) {
            if (process_list[i].active && process_list[i].processor_time > 0 && allocate_resources(&process_list[i])) {
                printf("Running Process ID %d for %d units in User Feedback.\n", process_list[i].process_id, TIME_SLICE);
                process_list[i].processor_time -= TIME_SLICE;
                if (process_list[i].processor_time > 0) {
                    process_list[i].priority--; // Lower the priority as feedback
                    all_done = 0;
                    printf("Process ID %d priority adjusted to %d.\n", process_list[i].process_id, process_list[i].priority);
                } else {
                    printf("Process ID %d completes execution in User Feedback.\n", process_list[i].process_id);
                    process_list[i].active = 0;
                }
                release_resources(&process_list[i]);
            }
        }
    } while (!all_done);
}

void mixedScheduler() {
    printf("\nExecuting Mixed Scheduler Mode:\n");
    resetProcesses(); FCFS();
    resetProcesses(); roundRobin();
    resetProcesses(); userFeedback();
}
void resetProcesses() {
    for (int i = 0; i < process_count; i++) {
        if (process_list[i].processor_time > 0) {
            process_list[i].active = 1;
        }
    }
}

void printProcessStatus() {
    printf("\nFinal Process Status:\n");
    for (int i = 0; i < process_count; i++) {
        printf("Process ID %d, Remaining Time: %d, Active: %d\n", process_list[i].process_id, process_list[i].processor_time, process_list[i].active);
    }
}
