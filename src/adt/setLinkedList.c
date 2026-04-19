/**
 * @file setLinkedList.c
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * @brief Provides an implementation of the ADT Set with a linked list as the underlying data structure.
 * @version 0.3
 * @date 2024-07-22
 * @copyright Copyright (c) 2024
 * 
 */

#include "adt/set.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

struct node;
typedef struct node* PtNode;

bool setContains(PtSet set, SetElem elem);

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

    if (set->header == NULL || set->trailer == NULL) {
        free(set->header);
        free(set->trailer);
        free(set);
        return NULL;
    }

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
    newNode->next = set->trailer;
    newNode->prev = set->trailer->prev;
    set->trailer->prev->next = newNode;
    set->trailer->prev = newNode;

    set->size++;

    return SET_OK;
}

int setRemove(PtSet set, SetElem elem){
    if (set == NULL) return SET_NULL;
    if (!setContains(set, elem)) return SET_MISSING_ELEM;

    PtNode curr = set->header->next;
    while (curr != set->trailer && strcmp(curr->element.disciplineName, elem.disciplineName) != 0) {
        curr =  curr->next;
    }

    if (curr == set->trailer) return SET_MISSING_ELEM; 

    PtNode prev = curr->prev;
    PtNode next = curr->next;
    prev->next = next;
    next->prev = prev;

    free(curr);

    set->size--;

    return SET_OK;
}

bool setContains(PtSet set, SetElem elem){
    if (set == NULL) return false;
    if (set->size == 0) return false;

    PtNode curr = set->header->next;
    while (curr != set->trailer) {
        if (strcmp(curr->element.disciplineName,elem.disciplineName) == 0) return true;
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
    if (subSet == NULL || set == NULL) return false;
    if (subSet->size == 0) return true;
    if (set->size == 0) return false;

    PtNode subCurr = subSet->header->next;

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

    PtNode curr = set->header->next;
    while (curr != set->trailer) {
        PtNode toFree = curr;
        curr = curr->next;
        free(toFree);
    }

    set->header->next = set->trailer;
    set->trailer->prev = set->header;

    set->size = 0;

    return SET_OK;
}

SetElem* setValues(PtSet set){
    if (set == NULL || set->size == 0) return NULL;

    SetElem* array = (SetElem*) malloc(set->size * sizeof(SetElem));
    if (array == NULL) return NULL;

    int count = 0;

    PtNode curr = set->header->next;
    while (curr != set->trailer) {
        array[count] = curr->element;
        count++;
        curr = curr->next;
    }

    return array;
}

void setPrint(PtSet set) {
    if (set == NULL) printf("SET NULL\n");
    else if (set->size == 0) printf("SET EMPTY\n");
    else {
        PtNode curr = set->header->next;
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