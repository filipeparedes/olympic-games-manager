/**
 * @file listings.c
 * @author Filipe Paredes (filipeparedes3@gmail.com)
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

#include "io/listings.h"
#include "adt/map.h"
#include "adt/mapElem.h"
#include "adt/list.h"
#include "adt/set.h"
#include "domain/athlete.h"
#include "domain/topnstats.h"

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
    printf("%d DISCIPLINES FOUND\n\n", size);

    printf("%30s", "DISCIPLINE");
	printf("%35s", "TOP MEDALS COUNTRY");
    printf("%15s", "PARTICIPATIONS");
    printf("===========================================================================================================================\n");

    setPrint(statistics);
}

void printHostDetails(char** hostData) {
    if (hostData == NULL) return;

    printf("\nHosting city: %s\n", hostData[0]);
    printf("Year: %s\n", hostData[1]);
    printf("Hosting country: %s\n", hostData[2]);
    printf("Duration of the event (days): %s\n\n", hostData[3]);
}

void printAthleteInfo(char** medalsStatistics, int medalsStatsSize, char* country, char* athleteID, int participations, int birthYear) {
    printf("\n=============== ATHLETE INFO ================\n");
    printf("AthleteID: %s\n", athleteID);
    printf("Birth Year: %d\n", birthYear);
    printf("Country: %s\n", country);
    printf("Number of Participations: %d\n\n", participations);
    printf("=================== MEDALS ===================\n");

    for (int i = 0; i<medalsStatsSize; i++) {
        printf("%s\n", medalsStatistics[i]);
    }
}

void printTopN(PtTopN topNList, int topNSize, int n) {
        printf("\n\n%-40s | %-12s | %-30s | %-28s\n", "Country", "Total medals", "Average medals by game edition", "Average medals by game day");
        printf("--------------------------------------------------------------------------------------------------------------------------\n");

        PtTopN sortedTopN = sortTopN(topNList, topNSize);

        if (n>topNSize) {
            for (int i = 0; i<topNSize; i++) {
             printf("%-40s | %-12d | %-30.2f | %-28.2f\n", sortedTopN[i].country, sortedTopN[i].totalMedals, sortedTopN[i].avgMedalsEdition, sortedTopN[i].avgMedalsGameDays);
            }

        } else {
            for (int i = 0; i<n; i++) {
             printf("%-40s | %-12d | %-30.2f | %-28.2f\n", sortedTopN[i].country, sortedTopN[i].totalMedals, sortedTopN[i].avgMedalsEdition, sortedTopN[i].avgMedalsGameDays);
            }
            printf("\n\nCould not find more than %d results.\n", topNSize);
        }
}

PtTopN sortTopN(PtTopN topNList, int topNSize){
    PtTopN sortedArray = topNList;

    for (int i = 0; i<topNSize; i++) {
        for (int j = 0; j<topNSize; j++) {
            if (sortedArray[j].totalMedals < sortedArray[j+1].totalMedals) {
                TopNStats temp;
                temp = sortedArray[j];
                sortedArray[j] = sortedArray[j+1];
                sortedArray[j+1] = temp; 
            } else if (sortedArray[j].totalMedals == sortedArray[j+1].totalMedals) {
                if (strcmp(sortedArray[j].country, sortedArray[j+1].country) > 0) {
                    TopNStats temp;
                    temp = sortedArray[j];
                    sortedArray[j] = sortedArray[j+1];
                    sortedArray[j+1] = temp;
                }

            }
        }
    }

    return sortedArray;
}

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


 