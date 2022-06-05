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

#define true = 1;
#define false = 0;

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

int GetMax2(const int *num1, const int *num2) { return (*num1 > *num2) * *num1 + (*num2 > *num1) * *num2; }


/***************************************************************/
/* Helpers */

void SetProcessId(Schedule *const ptr, int _id) { ptr->id = _id; }

void SetProcessArrivalTime(Schedule *const ptr, int _id) { ptr->arrival = _id; }

void SetProcessTotalCycleTime(Schedule *const ptr, int _id) { ptr->total_cpu = _id; }

int GetProcessDone(const Schedule *ptr) { return ptr->done; }

void SetProcessDone(Schedule *ptr, int val) { ptr->done = val; }

int GetProcessStarted(const Schedule *ptr) { return ptr->already_started; }

void SetProcessStarted(Schedule *ptr, int val) { ptr->already_started = val; }

Schedule *GetSchedule(int ndx){return P[ndx].schedule;}

void PrintMenu() {
    printf("\nBatch scheduling\n");
    printf("----------------\n");
    printf("1) Enter parameters\n");
    printf("2) Schedule processes with FIFO algorithm\n");
    printf("3) Schedule processes with SJF algorithm\n");
    printf("4) Schedule processes with SRT algorithm\n");
    printf("5) Quit and free memory\n\n");
    printf("Enter selection: ");
}


/***************************************************************/
/*"PROCEDURE TO PRINT THE CONTENTS OF THE SCHEDULING TABLE"*/
void PrintTable() {
    printf("\n%-8s%-8s%-8s%-8s%-8s%-8s\n", "ID", "Arrival", "Total", "Start", "End", "Turnaround");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < P_Length; i++) {
        GetProcessDone(P[i].schedule) ?
        printf("%-8d%-8d%-8d%-8d%-8d%-8d\n", P[i].schedule->id, P[i].schedule->arrival, P[i].schedule->total_cpu, P[i].schedule->start_time, P[i].schedule->end_time, P[i].schedule->turnaround_time):
        printf("%-8d%-8d%-8d\n", P[i].schedule->id, P[i].schedule->arrival, P[i].schedule->total_cpu);
    }
/* declare local variables */
/* print table header */
/* for each process */
/* print the contents (id, arrival time, total_cycles) of each field of the table's index */
/* if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time) */
    return;
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #1"*/
void Method1() {
/* declare local variables */
    if (P != NULL) {
        printf("Table already exists.....\nExiting method call\n");
        return;
    }
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
    PrintTable();
    /* prompt for total number of processes */
/* allocate memory for table to hold process parameters */
/* for each process */
/* prompt for process id, arrival time, and total cycle time */
/* print contents of table */
    return;
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #2"*/
void method2() {
/* declare (and initilize when appropriate) local variables */
/* for each process, reset "done" field to 0 */
/* while there are still processes to schedule */
/* initilize the earliest arrival time to INT_MAX (largest integer value) */
/* for each process not yet scheduled */
/* check if process has earlier arrival time than current earliest and update */
/* set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time */
/* update current cycle time and increment number of processes scheduled */
/* print contents of table */
    return;
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #3"*/
void method3() {
/* declare (and initilize when appropriate) local variables */
/* for each process, reset "done" field to 0 */
/* while there are still processes to schedule */
/* initilize the lowest total cycle time to INT_MAX (largest integer value) */
/* for each process not yet scheduled */
/* check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update */
/* set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time */
/* update current cycle time and increment number of processes scheduled */
/* print contents of table */
    return;
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #4"*/
void method4() {
/* declare (and initilize when appropriate) local variables */
/* for each process, reset "done", "total_remaining" and "already_started" fields to 0 */
/* while there are still processes to schedule */
/* initilize the lowest total remaining time to INT_MAX (largest integer value) */
/* for each process not yet scheduled */
/* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update */
/* check if process already partially-scheduled */
/* if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time */
/* set end time, turnaround time of process with lowest (and available) total remaining cycle time */
/* decrement total remaining time of process with lowest (and available) total remaining cycle time */
/* if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes*/
/* print contents of table */
    return;
}


/***************************************************************/
/*"PROCEDURE FOR OPTION #5"*/
void FreeAllMemory() {
/* free the schedule table if not NULL */
    return;
}


/***************************************************************/
int main() {
    int input = 0;
    while (input != 4) {
        PrintMenu();
        scanf("%d", &input);
        switch (input) {
            case 1:
                Method1();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                FreeAllMemory();
                printf("Quitting program...");
                break;
            default:
                printf("*** Invalid input ***\n");
                break;
        }

    }
    return 1;
    /* declare local vars */
    /* while user has not chosen to quit */
    /* print menu of options */
    /* prompt for menu selection */
    /* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */
} /* while loop */
/* indicates success */
/* end of procedure */

