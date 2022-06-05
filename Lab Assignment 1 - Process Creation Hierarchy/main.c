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
#include <ctype.h>

/* Define structures and global variables*/
typedef struct process_node {
    int process;
    struct process_node *child;
} Node;

typedef struct pcb_Node {
    int index;
    Node *Child;
    struct pcb_Node *Next;
} PCB;

PCB *Pcb_List = NULL;

int nextProcess = 1;


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

PCB *CreatePCB(int ndx) {
    PCB *node = malloc(sizeof(PCB));
    node->index = ndx;
    node->Child = NULL;
    node->Next = NULL;
    return node;
}

PCB *GetNodeByIndex(int ndx) {
    PCB *currNode = Pcb_List;
    if (ndx < 0)return NULL;
    int count = 0;
    while (count < ndx) {
        if (currNode->Next == NULL)return NULL;
        currNode = currNode->Next;
        count++;
    }
    return currNode;
}

int Pcb_Count() {
    PCB *currNode = Pcb_List;
    int count = 0;
    while (currNode != NULL) {
        currNode = currNode->Next;
        count++;
    }
    return count;
}

int Process_Count() {
    return nextProcess-1;
}


/***************************************************************/
/*PROCEDURE TO PRINT HIERARCHY OF PROCESSES*/
void PrintProcesses() {
    PCB *currNode = Pcb_List;
    while (currNode != NULL) {
        Node *currChild = currNode->Child;
        if (currChild == NULL) {
            currNode = currNode->Next;
            continue;
        }
        printf("PCB[%d] is the parent of:", currNode->index);
        while (currChild != NULL) {
            printf(" PCB[%d]", currChild->process);
            currChild = currChild->child;
        }
        printf("\n");
        currNode = currNode->Next;
    }
}


/***************************************************************/
/*PROCEDURE FOR OPTION #1*/
void CreatePcbList() {
    if (Pcb_List != NULL) {
        printf("List already exists..... Exiting method call\n");
        return;
    }
    int count;
    printf("Enter maximum number of processes: ");
    scanf("%d", &count);
    if (count == 0)return;
    Pcb_List = CreatePCB(0);
    Pcb_List->index = 0;
    PCB *currNode = Pcb_List;
    int currNdx = 1;
    while (currNdx < count) {
        currNode->Next = CreatePCB(currNdx);
        currNode = currNode->Next;
        currNode->index = currNdx;
        currNdx++;
    }
}


/***************************************************************/
/*PROCDURE FOR OPTION #2*/
void CreateProcess() {
    int index;
    printf("Enter the parent process index: ");
    scanf("%d", &index);
    PCB *target = GetNodeByIndex(index);
    if (target == NULL) {
        printf("Index %d does not exist.\n", index);
        return;
    }
    Node *child = target->Child;
    if (child == NULL) {
        target->Child = malloc(sizeof(Node));
        target->Child->process = nextProcess;
        nextProcess++;
        return;
    }
    while (child->child != NULL) {
        child = child->child;
    }
    child->child = malloc(sizeof(Node));
    child->child->process = nextProcess;
    nextProcess++;
}


/***************************************************************/
/*RECURSIVE PROCEDURE TO DESTROY CHILDREN PROCESSES*/
void DeleteChildren_Recurse(Node *toBeRemoved) {
    if (toBeRemoved == NULL)return;
    if (toBeRemoved->child != NULL) DeleteChildren_Recurse(toBeRemoved->child);
    free(toBeRemoved);
}

void DeleteChildren(int ndx) {
    PCB *target = GetNodeByIndex(ndx);
    if (target == NULL) {
        printf("Index %d does not exist.", ndx);
        return;
    }
    DeleteChildren_Recurse(target->Child);
    target->Child = NULL;
    target->index = -1;
}


/***************************************************************/
/*PROCEDURE FOR OPTION #3*/
void DeleteChildrenPrompt() {
    int index;
    printf("Enter the index of the process whose descendants are to be destroyed: ");
    scanf("%d", &index);
    DeleteChildren(index);
}


/***************************************************************/
/*PROCEDURE FOR OPTION #4*/
void FreeAllMemory() {
    PCB *curr;
    while (Pcb_Count() > 1) {
        curr = Pcb_List;
        while (curr->Next != GetNodeByIndex(Pcb_Count() - 1))curr = curr->Next;
        DeleteChildren(Pcb_Count() - 1);
        free(curr->Next);
        curr->Next = NULL;
    }
    DeleteChildren(Pcb_Count() - 1);
    free(Pcb_List);
    Pcb_List = NULL;
}


/***************************************************************/
int main() {
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
