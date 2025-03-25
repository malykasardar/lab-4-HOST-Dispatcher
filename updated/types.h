/*********************************************************************
 * Group Number: 1
 *   - Abdullah Hanoosh, Student ID: 100749026
 *   - Malyka Sardar, Student ID: 100752640
 *   - Marwan Alam, Student ID: 100842087
 *   - Vidurshan Sribalasuhabiramam, Student ID: 100558257
 *********************************************************************/
#ifndef TYPES_H
#define TYPES_H

#define MAX_PROCESSES 100
#define MEMORY_SIZE 1024
#define TIME_SLICE 5

typedef struct {
    int printers;
    int scanners;
    int modems;
    int cds;
} Resources;

extern Resources available_resources;

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
    int is_real_time;
    int active;
} Process;

extern Process process_list[MAX_PROCESSES];
extern int process_count;

void init_resources();
int allocate_resources(Process *p);
void release_resources(Process *p);
void executeProcesses();
void loadProcessesFromFile(const char* fileName);
void FCFS();
void roundRobin();
void userFeedback();
void mixedScheduler();
void resetProcesses();
void printProcessStatus();

#endif
