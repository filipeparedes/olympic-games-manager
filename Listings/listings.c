/**
 * @file listings.c
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Provides an implementation of listings.h
 * 
 * @version 0.4
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "listings.h"
#include "../ADTMap/map.h"
#include "../ADTMap/mapElem.h"
#include "../ADTList/list.h"
#include "../ADTSet/set.h"
#include "../Athlete/athlete.h"

PtList sortList(PtList athletes);

void paginate(PtList athletes) {
    int page = 0;
    int size = 0;
    int command;
    listSize(athletes, &size);
    PtList sortedList = sortList(athletes);

    printf("%d ATHLETES FOUND \n", size);

    if (size != 0) {
        bool whileOn = true;
        Athlete athlete;

        while (whileOn)
        {
            printf("%40s", "ATHLETE ID");
	        printf("%60s", "FULL NAME");
	        printf("%15s", "PARTICIPATIONS");
	        printf("%30s", "FIRST GAME");
	        printf("%12s\n", "BIRTH YEAR");
            printf("=====================================================================================================================================================================================\n");

            for(int i = page; i < size ; i++){
                if (i >= LISTINGS_PAGE_SIZE + page){
                    printf("\n");
                    break;
                } else{
                    listGet(sortedList, i, &athlete);
                    listElemPrint(athlete);
                }
                
            }
            printf("\nSHOWALL PAGINATED\n");
            if (LISTINGS_PAGE_SIZE < size - LISTINGS_PAGE_SIZE) 
                printf("1. Next %d\n", LISTINGS_PAGE_SIZE);
            printf("2. Return\n");
            
            readInteger(&command);

            if (command == 2)
                whileOn =false;
            else if (command == 1 && (LISTINGS_PAGE_SIZE < size - LISTINGS_PAGE_SIZE))
                page += LISTINGS_PAGE_SIZE;
            else
                printf("\nInvalid command.\n");
        }
    
    }

    free(sortedList);
}

void paginateSet(PtSet statistics){

    int size;
    setSize(statistics, &size);
    printf("Size: %d\n", size);

    setPrint(statistics);
}

void printHostDetails(char** hostData) {
    if (hostData == NULL) return;

    printf("\nHosting city: %s\n", hostData[0]);
    printf("Year: %s\n", hostData[1]);
    printf("Hosting country: %s\n", hostData[2]);
    printf("Duration of the event (days): %s\n\n", hostData[3]);
}

//TODO: make this a quick sort
PtList sortList(PtList athletes) {
    int listSizeVar;
    listSize(athletes, &listSizeVar);
    PtList sortedList = athletes;

    for (int i = 0; i < listSizeVar-1; i++) {
        for (int j = 0; j < listSizeVar-i-1; j++) { 

            Athlete elem, elem2;
            listGet(sortedList, j, &elem);
            listGet(sortedList, j+1, &elem2);

            if (strcmp(elem.athleteName, elem2.athleteName) > 0) {
                listSet(sortedList, j+1, elem, &elem2);
                listSet(sortedList, j, elem2, &elem);
            }
        }
    }
    
   return sortedList;
}


 