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

void *CreatePCB(int ndx) {
    PCB *node = malloc(sizeof(PCB));
    node->index = ndx;
    node->Child = NULL;
    node->Next = NULL;
    return node;
}

void *GetNodeByIndex(int ndx) {
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
    char rawInput;
    printf("Enter maximum number of processes: ");
    scanf("%s", &rawInput);
    if (!isdigit(rawInput)) {
        printf("***Invalid Input***\n");
        return;
    }
    count = rawInput - '0';
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
    char rawInput;
    printf("Enter the parent process index: ");
    scanf("%s", &rawInput);
    if (!isdigit(rawInput)) {
        printf("***Invalid Input***\n");
        return;
    }
    PCB *target = GetNodeByIndex(rawInput - '0');
    if (target == NULL) {
        printf("Index %d does not exist.\n", rawInput - '0');
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
void deleteChildren_recursiveHelper(Node *toBeRemoved) {
    if (toBeRemoved == NULL)return;
    if (toBeRemoved->child != NULL) deleteChildren_recursiveHelper(toBeRemoved->child);
    free(toBeRemoved);
}

void deleteChildren(int ndx) {
    PCB *target = GetNodeByIndex(ndx);
    if (target == NULL) {
        printf("Index %d does not exist.", ndx);
        return;
    }
    deleteChildren_recursiveHelper(target->Child);
    target->Child = NULL;
    target->index = -1;
}


/***************************************************************/
/*PROCEDURE FOR OPTION #3*/
void deleteChildrenPrompt() {
    char rawInput;
    printf("Enter the index of the process whose descendants are to be destroyed: ");
    scanf("%s", &rawInput);
    if (!isdigit(rawInput)) {
        printf("***Invalid Input***\n");
        return;
    }
    deleteChildren(rawInput - '0');
}


/***************************************************************/
/*PROCEDURE FOR OPTION #4*/
void freeAllMemory() {
    PCB *curr;
    while (Pcb_Count() > 1) {
        curr = Pcb_List;
        while (curr->Next != GetNodeByIndex(Pcb_Count() - 1))curr = curr->Next;
        deleteChildren(Pcb_Count() - 1);
        free(curr->Next);
        curr->Next = NULL;
    }
    deleteChildren(Pcb_Count() - 1);
    free(Pcb_List);
    Pcb_List = NULL;
}


/***************************************************************/
int main() {
    int input = 0;
    char rawInput = 'a';
    while (input != 4) {
        PrintMenu();
        scanf("%s", &rawInput);
        if (isdigit(rawInput)) input = rawInput - '0';
        switch (input) {
            case 1:
                CreatePcbList();
                break;
            case 2:
                CreateProcess();
                PrintProcesses();
                break;
            case 3:
                deleteChildrenPrompt();
                PrintProcesses();
                break;
            case 4:
                freeAllMemory();
                printf("Quitting program...");
                break;
            default:
                printf("*** Invalid input ***\n");
                break;
        }

    }
    return 0;
}
