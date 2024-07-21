/**
 * @file setLinkedList.c
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Provides an implementation of the ADT Set with a linked array list as the underlying data structure.
 * @version 0.3
 * @date 2024-07-22
 * @copyright Copyright (c) 2024
 * 
 */

#include "set.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

struct node;
typedef struct node* PtNode;

typedef struct node {
    SetElem element;
    PtNode next, prev;
} Node;

typedef struct setImpl {
    PtNode header, trailer;
    int size;
} SetImpl;

PtSet setCreate() {
    PtSet set = (PtSet) malloc(sizeof(SetImpl));
    if (set == NULL) return NULL;

    set->header = (PtNode)malloc(sizeof(Node));
    set->trailer = (PtNode)malloc(sizeof(Node));

    set->header->next = set->trailer;
    set->header->prev = NULL;

    set->trailer->prev = set->header;
    set->trailer->next = NULL;

    set->size = 0;

    return set;
}

int setAdd(PtSet set, SetElem elem) {
    if (set == NULL) return SET_NULL;
    if (setContains(set, elem)) return SET_DUPLICATE;

    PtNode newNode = (PtNode) malloc(sizeof(Node));
    if (newNode == NULL) return SET_NO_MEMORY;

    newNode->element = elem;
    newNode->next = NULL;
    newNode->prev = set->trailer;
    set->trailer->next = newNode;
    set->trailer = newNode;

    set->size++;

    return SET_OK;
}

int setRemove(PtSet set, SetElem elem){
    if (set == NULL) return SET_NULL;
    if (!setContains(set, elem)) return SET_MISSING_ELEM;

    PtNode curr = set->header;
    while (curr->element != elem) {
        curr =  curr->next;
    }

    PtNode next = curr->next;
    PtNode prev = curr->prev;
    prev->next = next;
    next->prev = prev;

    free(curr);

    set->size--;

    return SET_OK;
}

bool setContains(PtSet set, SetElem elem){
    if (set->size == 0 || set == NULL || elem == NULL) return false;

    PtNode curr = set->header;
    while (curr->next != set->trailer) {
        if (curr->element == elem) return true;

        curr = curr->next;
    }

    return false;
}

int setSize(PtSet set, int *ptSize) {
    if (set == NULL) return SET_NULL;

    *ptSize = set->size;

    return SET_OK;
}

bool setSubset(PtSet subSet, PtSet set) {
    if (subSet == NULL || set == NULL || subSet->size == 0 || set->size == 0) return false;

    PtNode subCurr = subSet->header;

    while (subCurr != subSet->trailer) {
        if (!setContains(set, subCurr->element)) return false;
        subCurr = subCurr->next;
    }

    return true;
}

bool isSetEmpty(PtSet set){
    if (set == NULL) return true;

    return (set->size == 0);
}

int setClear(PtSet set) {
    if (set == NULL) return SET_NULL;

    PtNode curr = set->header;
    while (curr != set->trailer) {
        curr = curr->next;
        free(curr->prev);
    }

    set->header->next = set->trailer;
    set->trailer->prev = set->header;

    set->size = 0;

    return SET_OK;
}

SetElem* setValues(PtSet set){
    if (set == NULL || set->size == 0) return NULL;

    SetElem* array = (SetElem*) malloc(set->size*sizeof(SetElem));
    int count = 0;

    PtNode curr = set->header;
    while (curr != set->trailer) {
        array[count] = curr->element;
        count++;
        curr = curr->next;
    }

    return array;
}

void setPrint(PtSet set) {
    if (set == NULL) printf("LIST NULL\n");
    else if (set->size == 0) printf("LIST EMPTY\n");
    else {
        PtNode curr = set->header;

        while(curr != set->trailer) {
            setElemPrint(curr->element);
            printf("\n");

            curr = curr->next;
        }
    }
    printf("\n");
}

int setDestroy(PtSet *ptSet) {
    PtSet set = *ptSet;
    if(set == NULL) return SET_NULL;

    PtNode curr = set->header;
    while(curr != NULL) {
        PtNode remove = curr;
        curr = curr->next;
        free(remove);
    }

    free(set);

    *ptSet = NULL;

    return SET_OK;
}