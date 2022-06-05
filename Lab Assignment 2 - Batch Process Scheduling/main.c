/*
 *
 * Dylan Moon
 * CSUN
 * Summer 2022
 * COMP 322 - 10543
 * Lab Assignment 1
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/* declare global variables including a table structure to hold scheduling information */
typedef struct prc {
    int id;
    int done;
    int already_started;
    int total_cpu;
    int arrival;
    int total_remaining;
    int turnaround_time;
    int start_time;
    int end_time;
} Schedule;

Schedule *Schedule_init(Schedule *const ptr) {
    ptr->id = 0;
    ptr->done = 0;
    ptr->already_started = 0;
    ptr->total_cpu = 0;
    ptr->arrival = 0;
    ptr->total_remaining = 0;
    ptr->turnaround_time = 0;
    ptr->start_time = 0;
    ptr->end_time = 0;
    return ptr;
}

Schedule *NewSchedule() { return Schedule_init(malloc(sizeof(Schedule))); }


typedef struct arr {
    Schedule *schedule;
} Table;
Table *P;

int P_Length;

/* optional: define a function that finds the maximum of two integers */
int GetMax(const int *num1, const int *num2) { return *num1 > *num2 ? *num1 : *num2; }
int GetMin(const int *num1, const int *num2) { return *num1 < *num2 ? *num1 : *num2; }


/***************************************************************/
/* Helpers */

void PrintMenu() {
    printf("\nBatch scheduling\n----------------\n1) Enter parameters\n2) Schedule processes with FIFO algorithm\n3) Schedule processes with SJF algorithm\n4) Schedule processes with SRT algorithm\n5) Quit and free memory\n\nEnter selection: ");
}
void ResetDone(){
    for (int i = 0; i < P_Length; i++) {
        P[i].schedule->done = 0;
        P[i].schedule->already_started = 0;
        P[i].schedule->start_time = 0;
        P[i].schedule->end_time = 0;
        P[i].schedule->turnaround_time = 0;
    }}
void FreeAllMemory();
int ProcessToSchedule(){
    for (int i = 0; i < P_Length; i++) {
        if(P[i].schedule->done)continue;
        return 1;
    }
    return 0;
}


/***************************************************************/
/*"PROCEDURE TO PRINT THE CONTENTS OF THE SCHEDULING TABLE"*/
void PrintTable() {
    printf("\n%-8s%-8s%-8s%-8s%-8s%-8s\n--------------------------------------------------\n", "ID", "Arrival", "Total", "Start", "End", "Turnaround");
    for (int i = 0; i < P_Length; i++) {
        printf("%-8d%-8d%-8d", P[i].schedule->id, P[i].schedule->arrival, P[i].schedule->total_cpu);
        if(P[i].schedule->done)printf("%-8d%-8d%-8d", P[i].schedule->start_time, P[i].schedule->end_time, P[i].schedule->turnaround_time);
        printf("\n");
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #1"*/
void Method1() {
    if (P != NULL)FreeAllMemory();
    printf("Enter total number of processes: ");
    scanf("%d", &P_Length);
    if (P_Length == 0)return;
    P = malloc(sizeof(Table) * P_Length);
    for (int i = 0; i < P_Length; i++) {
        P[i].schedule = NewSchedule();
        printf("Enter process id: ");
        scanf("%d", &P[i].schedule->id);
        printf("Enter arrival cycle for process P[%d]: ", i+1);
        scanf("%d", &P[i].schedule->arrival);
        printf("Enter total cycles for process P[%d]: ", i+1);
        scanf("%d", &P[i].schedule->total_cpu);
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #2"*/
void method2() {
    ResetDone();
    int startTime = 0;
    while (ProcessToSchedule()){
        int earliestArrival = INT_MAX;
        Schedule *curr;
        for (int i = 0; i < P_Length; i++) {
            if(P[i].schedule->done)continue;
            if(P[i].schedule->arrival < earliestArrival){
                earliestArrival = P[i].schedule->arrival;
                curr = P[i].schedule;
            }
        }
        curr->start_time = startTime;
        curr->end_time = startTime + curr->total_cpu;
        startTime = curr->end_time;
        curr->turnaround_time = curr->end_time - curr->arrival;
        curr->done = 1;
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #3"*/
void method3() {
    ResetDone();
    int currentCycleTime = 0;
    while(ProcessToSchedule()){
        int lowestTotalCycleTIme= INT_MAX, lowestStartTime = INT_MAX;
        Schedule *curr;
        for (int i = 0; i <P_Length; i++) {
            if(P[i].schedule->done)continue;
            if(P[i].schedule->arrival <= currentCycleTime && P[i].schedule->total_cpu < lowestTotalCycleTIme){
                curr = P[i].schedule;
                lowestTotalCycleTIme = curr->total_cpu;
            }
        }
        curr->start_time = currentCycleTime;
        curr->end_time = currentCycleTime + curr->total_cpu;
        currentCycleTime = curr->end_time;
        curr->turnaround_time = curr->end_time - curr->arrival;
        curr->done = 1;
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #4"*/
void method4() {
/* declare (and initilize when appropriate) local variables */
/* for each process, reset "done", "total_remaining" and "already_started" fields to 0 */
ResetDone();
/* while there are still processes to schedule */
/* initilize the lowest total remaining time to INT_MAX (largest integer value) */
/* for each process not yet scheduled */
/* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update */
/* check if process already partially-scheduled */
/* if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time */
/* set end time, turnaround time of process with lowest (and available) total remaining cycle time */
/* decrement total remaining time of process with lowest (and available) total remaining cycle time */
/* if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes*/
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #5"*/
void FreeAllMemory() {
    if(P == NULL)return;
    for (int i = 0; i < P_Length; i++) {
        free(P[i].schedule);
        P[i].schedule = NULL;
    }
    free(P);
    P = NULL;
}


/***************************************************************/
int main() {
    int input = 0;
    do {
        PrintMenu();
        scanf("%d", &input);
        switch (input) {
            case 1:
                Method1();
                PrintTable();
                break;
            case 2:
                method2();
                PrintTable();
                break;
            case 3:
                method3();
                PrintTable();
                break;
            case 4:
                method4();
                PrintTable();
                break;
            case 5:
                FreeAllMemory();
                printf("Quitting program...");
                break;
            default:
                printf("*** Invalid input ***\n");
                break;
        }
    } while (input != 5);
    return 1;
}