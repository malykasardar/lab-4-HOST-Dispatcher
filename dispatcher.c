#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100
#define TIME_SLICE 5

// Process structure
typedef struct Process {
    int pid;
    int priority;
    int burstTime;
    int remainingTime;
    struct Process* next;
} Process;

// Dispatcher structure
typedef struct Dispatcher {
    Process* queue;
} Dispatcher;

// Function to create a new process
Process* createProcess(int pid, int priority, int burstTime) {
    Process* newProcess = (Process*)malloc(sizeof(Process));
    newProcess->pid = pid;
    newProcess->priority = priority;
    newProcess->burstTime = burstTime;
    newProcess->remainingTime = burstTime;
    newProcess->next = NULL;
    return newProcess;
}

// Add process to the queue
void addProcess(Dispatcher* dispatcher, Process* newProcess) {
    if (!dispatcher->queue) {
        dispatcher->queue = newProcess;
    } else {
        Process* temp = dispatcher->queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newProcess;
    }
}

// FCFS Scheduler (First Come First Served)
void FCFS(Dispatcher* dispatcher) {
    Process* current = dispatcher->queue;
    while (current) {
        printf("Executing Process %d\n", current->pid);
        current = current->next;
    }
}

// Round Robin Scheduler
void roundRobin(Dispatcher* dispatcher) {
    Process* current = dispatcher->queue;
    while (current) {
        printf("Executing Process %d for %d units\n", current->pid, TIME_SLICE);
        current->remainingTime -= TIME_SLICE;
        if (current->remainingTime > 0) {
            addProcess(dispatcher, current);
        }
        current = current->next;
    }
}

// User Feedback Scheduler
void userFeedback(Dispatcher* dispatcher) {
    Process* current = dispatcher->queue;
    while (current) {
        if (current->remainingTime > TIME_SLICE) {
            printf("Executing Process %d for %d units\n", current->pid, TIME_SLICE);
            current->remainingTime -= TIME_SLICE;
            addProcess(dispatcher, current);
        } else {
            printf("Executing Process %d for %d units\n", current->pid, current->remainingTime);
            current->remainingTime = 0;
        }
        current = current->next;
    }
}
