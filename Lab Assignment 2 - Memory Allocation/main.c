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
    if (node->next) node->next->previous = node->previous;
    if (node->previous) node->previous->next = node->next;
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

int InsertNode(Block *node, Block *newNode) {
    if (!node || !newNode)return 0;
    if (node->next) {
        node->next->previous = newNode;
        newNode->next = node->next;
    }
    node->next = newNode;
    newNode->previous = node;
    return 1;
}

int FirstFit(const int *id, const int *size) {
    Block *curr = list;
    while (curr) {
        if (curr->next && *size <= curr->next->startAddress - curr->endAddress) {//mid list
            return InsertNode(curr, InitializeBlock(*id, curr->endAddress, curr->endAddress + *size));
        }
        if (!curr->next && *size <= pm_size - curr->endAddress) {//tail of list
            return InsertNode(curr, InitializeBlock(*id, curr->endAddress, curr->endAddress + *size));
        }
        curr = curr->next;
    }
    return 0;
}

int BestFit(const int *id, const int *size) {
    int smallestHole = pm_size;
    Block *curr = list;
    Block *bestFit = NULL;
    while (curr) {
        if (curr->next) {//mid list
            int holeSize = curr->next->startAddress - curr->endAddress;
            if (holeSize && holeSize >= *size && holeSize < smallestHole) {
                smallestHole = holeSize;
                bestFit = curr;
            }
        } else { //end of list
            int holeSize = pm_size - curr->endAddress;
            if (holeSize && holeSize >= *size && holeSize < smallestHole) {
                bestFit = curr;
            }
        }
        curr = curr->next;
    }
    if (bestFit) {
        return InsertNode(bestFit, InitializeBlock(*id, bestFit->endAddress, bestFit->endAddress + *size));
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
}

void AllocBlock() {
    int id;
    printf("Enter block id: ");
    scanf("%d", &id);
    int size;
    printf("Enter block size: ");
    scanf("%d", &size);
    if (!list) {
        if(pm_size < size){
            printf("Error, %d units of memory not found.\n", size);
        }
        else{
            list = InitializeBlock(id, 0, size);
        }
        return;
    }
    if (IdExists(&id)) {
        printf("Error, id already exists.\n");
        return;
    }
    if (a_type ? BestFit(&id, &size) : FirstFit(&id, &size))return;
    printf("Error, %d units of memory not found.\n", size);
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