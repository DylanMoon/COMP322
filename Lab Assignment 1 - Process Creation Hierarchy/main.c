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

/* Define structures and global variables*/
typedef struct node1 linkedList;
typedef struct node2 PcbNode;

struct node1 {
    int process;
    linkedList *link;
};

struct node2 {
    int parent;
    linkedList *children;
};

PcbNode *PCB;
int count;

/***************************************************************/
/* Helpers */

void PrintMenu() {
    printf("\nProcess creation and destruction\n");
    printf("--------------------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Create a new child process\n");
    printf("3) Destroy all descendants of a process\n");
    printf("4) Quit program and free memory\n\n");
    printf("Enter selection: ");
}

void InitializePCB(PcbNode *node) {
    node->parent = -1;
    node->children = NULL;
}

void Append(linkedList *list, linkedList *newNode){
    linkedList *curr = list;
    while(curr ->link != NULL){
        curr = curr->link;
    }
    curr->link = newNode;
}

int GetNextWithoutParent(){
    for (int i = 0; i < count; i++) {
        if(PCB[i].parent == -1) {return i;}
    }
    return -1;
}

/***************************************************************/
/*PROCEDURE TO PRINT HIERARCHY OF PROCESSES*/
void PrintProcesses() {
    for (int i = 0; i < count; i++) {
        if ((PCB[i].parent != -1) && (PCB[i].children != NULL)) {
            printf("PCB[%d] is the parent of", i);
            linkedList *next = PCB[i].children;
            while (next != NULL) {
                printf(" PCB[%d]", next->process);
                next = next->link;
            }
            printf("\n");
        }
    }
}

/***************************************************************/
/*PROCEDURE FOR OPTION #1*/
void CreatePcbList() {
    printf("Enter maximum number of processes: ");
    scanf("%d", &count);
    if (count == 0)return;
    PCB = (PcbNode *) malloc(count * sizeof(PcbNode));
    for (int i = 0; i < count; i++) {
        InitializePCB(&PCB[i]);
    }
    PCB[0].parent=0;
}


/***************************************************************/
/*PROCDURE FOR OPTION #2*/
void CreateProcess() {
    //TODO: this is not working
    int p;
    printf("Enter the parent process p: ");
    scanf("%d", &p);
    PcbNode *target = &PCB[p];
    int q = GetNextWithoutParent();
    PCB[q].parent = p;
    linkedList *newChild = malloc(sizeof(linkedList));
    newChild->link = NULL;
    newChild->process = q;
    linkedList *curr = target->children;
    if(curr == NULL){
        target->children = newChild;
    }
    else
    {
        Append(curr, newChild);
    }
}

/***************************************************************/
/*RECURSIVE PROCEDURE TO DESTROY CHILDREN PROCESSES*/

void DeleteChildRecurse(linkedList *node) {
    //TODO: this is horrible sig fault right now
    if (node == NULL)return;
    DeleteChildRecurse(node->link);
    int q = node->process;
    DeleteChildRecurse(PCB[q].children);
    free(node);
    PCB[q].parent = -1;
    PCB[q].children = NULL;
}

/***************************************************************/
/*PROCEDURE FOR OPTION #3*/
void DeleteChildrenPrompt() {
    int index;
    printf("Enter the index of the process whose descendants are to be destroyed: ");
    scanf("%d", &index);
    DeleteChildRecurse(PCB[index].children);
    PCB[index].children = NULL;
}


/***************************************************************/
/*PROCEDURE FOR OPTION #4*/
void FreeAllMemory() {
    if(PCB == NULL)return;

}


/***************************************************************/
int main() {
    count = 0;
    int input = 0;
    while (input != 4) {
        PrintMenu();
        scanf("%d", &input);
        switch (input) {
            case 1:
                CreatePcbList();
                break;
            case 2:
                CreateProcess();
                PrintProcesses();
                break;
            case 3:
                DeleteChildrenPrompt();
                PrintProcesses();
                break;
            case 4:
                FreeAllMemory();
                printf("Quitting program...");
                break;
            default:
                printf("*** Invalid input ***\n");
                break;
        }

    }
    return 1;
}
