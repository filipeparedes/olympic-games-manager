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

MapValue* sortMapValues(PtMap athletes);

void paginate(PtMap athletes) {
    int page = 0;
    int size = 0;
    int command;
    mapSize(athletes, &size);
    Athlete* sortedMapVal = sortMapValues(athletes);

    printf("%d ATHLETES FOUND \n", size);

    if (size != 0) {
        bool whileOn = true;

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
                } else
                    mapValuePrint(sortedMapVal[i]);
                
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

    free(sortedMapVal);
}

void printHostDetails(char** hostData) {
    if (hostData == NULL) return;

    printf("\nHosting city: %s\n", hostData[0]);
    printf("Year: %s\n", hostData[1]);
    printf("Hosting country: %s\n", hostData[2]);
    printf("Duration of the event (days): %s\n\n", hostData[3]);
}

//TODO: make this a quick sort
MapValue* sortMapValues(PtMap athletes) {
    int mapSizeVar;
    mapSize(athletes, &mapSizeVar);
    Athlete temp;
    Athlete* values = mapValues(athletes);

    for (int i = 0; i < mapSizeVar - 1; i++) {
        for (int j = 0; j < mapSizeVar -i -1; j++) { 

            if (strcmp(values[j].athleteName, values[j+1].athleteName) > 0) {
                temp = values[j+1];
                values[j+1] = values[j];
                values[j] = temp;
            }
        }
    }
    
   return values;
}


 