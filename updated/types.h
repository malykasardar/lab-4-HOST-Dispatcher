#ifndef TYPES_H
#define TYPES_H

#define MAX_PROCESSES 100
#define MEMORY_SIZE 1024
#define TIME_SLICE 5 

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

#endif





/*********************************************************************
 * Group Number: 1
 *   - Abdullah Hanoosh, Student ID: 100749026
 *   - Malyka Sardar, Student ID: 100752640
 *   - Marwan Alam, Student ID: 100842087
 *   - Vidurshan Sribalasuhabiramam, Student ID: 100558257
 *********************************************************************/
