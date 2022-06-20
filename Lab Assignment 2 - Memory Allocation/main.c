/*
 *
 * Dylan Moon
 * CSUN
 * Summer 2022
 * COMP 322 - 10543
 * Lab Assignment 2
 *
 * */

#include <stdio.h>
#include <stdlib.h>

typedef struct blockInformation {
    int id;
    int startAddress;
    int endAddress;
    struct blockInformation *previous;
    struct blockInformation *next;

} Block;

Block *list = NULL;
int pm_size; // physical memory size
int a_type; // algorithm type (0 = first fit, 1 = best fit)

void PrintMenu() {
    printf("\nMemory allocation\n");
    printf("--------------------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Allocate memory for block\n");
    printf("3) Deallocate memory for block\n");
    printf("4) Defragment memory\n");
    printf("5) Quit program\n\n");
    printf("Enter selection: ");
}

void FreeAllMemory();

Block *InitializeBlock(int id, int start, int end) {
    Block *temp = malloc(sizeof(Block));
    temp->id = id;
    temp->startAddress = start;
    temp->endAddress = end;
    temp->previous = temp->next = NULL;
    return temp;
}

void FreeBlock(Block *node) {
    if (node->next)node->next->previous = node->previous;
    if (node->previous)node->previous->next = node->next;
    else {
        list = node->next;
    }
    free(node);
}

int IdExists(const int *id) {
    Block *curr = list;
    while (curr) {
        if (curr->id == *id)return 1;
        curr = curr->next;
    }
    return 0;
}

void PrintTable() {
    printf("\n%-6s%-8s%-6s\n-------------------\n", "ID", "Start", "End");
    Block *curr = list;
    while (curr) {
        printf("%-6d%-8d%-6d\n", curr->id, curr->startAddress, curr->endAddress);
        curr = curr->next;
    }
}

int FirstFit(const int *id, const int *size) {
    Block *curr = list;
    while (curr) {
        if (curr->next && *size < curr->next->startAddress - curr->endAddress) {//mid list
            Block *newNode = InitializeBlock(*id, curr->endAddress, curr->endAddress + *size);
            newNode->previous = curr;
            curr->next->previous = newNode;
            newNode->next = curr->next;
            curr->next = newNode;
            return 1;
        }
        if (!curr->next && *size < pm_size - curr->endAddress) {//tail of list
            Block *newNode = InitializeBlock(*id, curr->endAddress, curr->endAddress + *size);
            curr->next = newNode;
            newNode->previous = curr;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int BestFit(int id, int size) {
// best-fit algorithm
// if hole is smaller than best so far
// set values of best start & best end & best hole size so far
// update best block & advance next block
// set start & end fields of new block & add block into linked list
// reduce remaining available memory and return
    Block *curr = list;
    while (curr) {

        curr = curr->next;
    }
    return 0;
}

void EnterParams() {
    pm_size = 0;
    a_type = 0;
    if (list)FreeAllMemory();
    printf("Enter size of physical memory: ");
    scanf("%d", &pm_size);
    printf("Enter hole-fitting algorithm (0=first fit, 1=best_fit): ");
    scanf("%d", &a_type);
    list = InitializeBlock(-1, 0, 0);
}

/********************************************************************/
/*"OPTION #2"*/
void AllocBlock() {
    int id;
    printf("Enter block id: ");
    scanf("%d", &id);
    int size;
    printf("Enter block size: ");
    scanf("%d", &size);
    if (IdExists(&id)) {
        printf("Error, id already exists.\n");
        return;
    }
    if (list->endAddress - list->startAddress == 0) {
        //the only node that exists is the dummy block
        FreeBlock(list);
        list = InitializeBlock(id, 0, size);
        return;
    }
    if (a_type ? BestFit(id, size) : FirstFit(&id, &size))return;
    printf("Error, could not find %d units of space.\n", size);
}

void DeallocBlock() {
    int id_to_remove;
    printf("Enter block id: ");
    scanf("%d", &id_to_remove);
    Block *curr = list;
    while (curr) {
        if (id_to_remove == curr->id)break;
        curr = curr->next;
    }
    if (!curr) {
        printf("Id not found.\n");
        return;
    }
    FreeBlock(curr);
}

void Defragment() {
    Block *curr = list;
    while (curr) {
        if (curr->previous) {
            curr->endAddress = curr->endAddress - (curr->startAddress - curr->previous->endAddress);
            curr->startAddress = curr->previous->endAddress;
        } else {
            //head of list
            curr->endAddress = curr->endAddress - curr->startAddress;
            curr->startAddress = 0;
        }
        curr = curr->next;
    }
}

void FreeBlockRecurse(Block *node) {
    if (!node)return;
    FreeBlockRecurse(node->next);
    if (node->previous)node->previous->next = NULL;
    free(node);
}

void FreeAllMemory() {
    FreeBlockRecurse(list);
    list = NULL;
}

int main() {
    int input = 0;
    while (input != 5) {
        PrintMenu();
        scanf("%d", &input);
        switch (input) {
            case 1:
                EnterParams();
                break;
            case 2:
                AllocBlock();
                PrintTable();
                break;
            case 3:
                DeallocBlock();
                PrintTable();
                break;
            case 4:
                Defragment();
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
    }
    return 1;
}