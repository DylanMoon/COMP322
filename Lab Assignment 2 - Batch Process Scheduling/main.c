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

void ResetSchedule(Schedule *curr) {
        curr->done = 0;
        curr->already_started = 0;
        curr->start_time = 0;
        curr->end_time = 0;
        curr->turnaround_time = 0;
        curr->total_remaining = 0;
}

void ResetSchedules(){
    for (int i = 0; i < P_Length; i++) {ResetSchedule(P[i].schedule);}
}

void FreeAllMemory();

int ProcessToSchedule() {
    for (int i = 0; i < P_Length; i++) {
        if (P[i].schedule->done)continue;
        return 1;
    }
    return 0;
}

void UpdateSchedule(Schedule *curr, int *currCycleTime) {
    curr->start_time = *currCycleTime;
    curr->end_time = *currCycleTime + curr->total_cpu;
    *currCycleTime = curr->end_time;
    curr->turnaround_time = curr->end_time - curr->arrival;
    curr->done = 1;
}


/***************************************************************/
/*"PROCEDURE TO PRINT THE CONTENTS OF THE SCHEDULING TABLE"*/
void PrintTable() {
    printf("\n%-8s%-8s%-8s%-8s%-8s%-8s\n--------------------------------------------------\n", "ID", "Arrival", "Total",
           "Start", "End", "Turnaround");
    for (int i = 0; i < P_Length; i++) {
        printf("%-8d%-8d%-8d", P[i].schedule->id, P[i].schedule->arrival, P[i].schedule->total_cpu);
        if (P[i].schedule->done)
            printf("%-8d%-8d%-8d", P[i].schedule->start_time, P[i].schedule->end_time, P[i].schedule->turnaround_time);
        printf("\n");
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #1"*/
void EnterParams() {
    if (P != NULL)FreeAllMemory();
    printf("Enter total number of processes: ");
    scanf("%d", &P_Length);
    if (P_Length == 0)return;
    P = malloc(sizeof(Table) * P_Length);
    for (int i = 0; i < P_Length; i++) {
        P[i].schedule = NewSchedule();
        printf("Enter process id: ");
        scanf("%d", &P[i].schedule->id);
        printf("Enter arrival cycle for process P[%d]: ", i + 1);
        scanf("%d", &P[i].schedule->arrival);
        printf("Enter total cycles for process P[%d]: ", i + 1);
        scanf("%d", &P[i].schedule->total_cpu);
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #2"*/
/*First come, first served*/
void ScheduleFIFO() {
    ResetSchedules();
    int currCycleTime = 0;
    while (ProcessToSchedule()) {
        int earliestArrival = INT_MAX;
        Schedule *curr;
        for (int i = 0; i < P_Length; i++) {
            if (P[i].schedule->done)continue;
            if (P[i].schedule->arrival < earliestArrival) {
                earliestArrival = P[i].schedule->arrival;
                curr = P[i].schedule;
            }
        };
        UpdateSchedule(curr, &currCycleTime);
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #3"*/
/*Shortest Job First*/
void ScheduleSJF() {
    ResetSchedules();
    int currCycleTime = 0;
    while (ProcessToSchedule()) {
        int lowestTotalCycleTIme = INT_MAX, lowestStartTime = INT_MAX;
        Schedule *curr;
        for (int i = 0; i < P_Length; i++) {
            if (P[i].schedule->done)continue;
            if (P[i].schedule->arrival <= currCycleTime && P[i].schedule->total_cpu < lowestTotalCycleTIme) {
                curr = P[i].schedule;
                lowestTotalCycleTIme = curr->total_cpu;
            }
        }
        UpdateSchedule(curr, &currCycleTime);
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #4"*/
/*Shortest Remaining Time*/
void ScheduleSRT() {
    ResetSchedules();
    while (ProcessToSchedule()){
        /* initilize the lowest total remaining time to INT_MAX (largest integer value) */
        /* for each process not yet scheduled */
        /* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update */
        /* check if process already partially-scheduled */
        /* if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time */
        /* set end time, turnaround time of process with lowest (and available) total remaining cycle time */
        /* decrement total remaining time of process with lowest (and available) total remaining cycle time */
        /* if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes*/
    }
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #5"*/
void FreeAllMemory() {
    if (P == NULL)return;
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
                EnterParams();
                PrintTable();
                break;
            case 2:
                ScheduleFIFO();
                PrintTable();
                break;
            case 3:
                ScheduleSJF();
                PrintTable();
                break;
            case 4:
                ScheduleSRT();
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