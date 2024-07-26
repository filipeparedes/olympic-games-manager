/**
 * @file logic.c
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Contains implementation for logic.h
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

#include "logic.h"
#include "../ADTMap/mapElem.h"
#include "../ADTMap/map.h"
#include "../ADTSet/set.h"
#include "../ADTSet/setElem.h"
#include "../ADTList/list.h"
#include "../ADTList/listElem.h"
#include "../Medal/medal.h"
#include "../DisciplineStats/disciplinestats.h"

PtList filterListByParticipations(PtList athletes, int participations){

    int orgListSize;
    listSize(athletes, &orgListSize);
    if (orgListSize == 0) {
        printf("The original list is empty.\n");
        return NULL;
    }

    PtList filteredList = listCreate();
    if (filteredList == NULL){
        printf("Failed to create a filtered list.\n");
        return NULL;
    }

    for (int i = 0, j=0; i < orgListSize; i++) {
        Athlete athlete;

        if (listGet(athletes, i, &athlete) == LIST_OK) {
            if (athlete.gamesParticipations >= participations){
                listAdd(filteredList, j++, athlete);
            }
        }
    }

    return filteredList;
}

PtList filterListByFirstYear(PtList athletes, char* firstYear){

    int orgListSize;
    listSize(athletes, &orgListSize);
    if (orgListSize == 0) {
        printf("The original list is empty.\n");
        return NULL;
    }

    PtList filteredList = listCreate();
    if (filteredList == NULL){
        printf("Failed to create filtered list.\n");
        return NULL;
    }

    for (int i = 0, j=0; i < orgListSize; i++) {
        Athlete athlete;

        if (listGet(athletes, i, &athlete) == LIST_OK) {
            int len = strlen(athlete.firstGame);
            if (len >= 4) { 
                char* year = athlete.firstGame + (len - 4); //Extracts the last four digits of the string 
                if (strcmp(year, firstYear) == 0){
                    listAdd(filteredList, j++, athlete);
                }
            }
        }
    }
    return filteredList;
}

char** getHostData(PtMap hosts, char* editionName){

    int orgMapSize;
    mapSize(hosts, &orgMapSize);

    if (orgMapSize == 0){
        printf("The original map is empty.\n");
        return NULL;
    }

    MapKey* keys = mapKeys(hosts);

    char** data = (char**)malloc(4 * sizeof(char*));

    if (data == NULL) {
        printf("Failed to create the data array.\n");
        return NULL;
    }

    //Aloca memória para as strings dentro do array
    for (int i = 0; i < 4; i++) {
        data[i] = (char*)malloc(50 * sizeof(char));
        if (data[i] == NULL) {
            printf("Failed to allocate memory for a string.\n");
            for (int j = 0; j < i; j++) {
                free(data[j]);
            }
            free(data);
            return NULL;
        }
    }

    Host searchedHost;
    bool found = false;
    
    for (int i = 0; i<orgMapSize; i++) {
        Host host;
        mapGet(hosts, keys[i], &host);
        if (strcmp(host.gameName,editionName) == 0){
            searchedHost = host;
            found = true;
        }
    }

    if (!found)
    {
         printf("No edition found."); 
         free(data);
         data = NULL;
         return NULL;
    }

    int gameNameLen = strlen(searchedHost.gameName);
    if (gameNameLen > 5) {
        strncpy(data[0], searchedHost.gameName, gameNameLen-4);
        data[0][gameNameLen-5] = '\0';
    } 
    else strcpy(data[0], "");
    
    sprintf(data[1], "%d", searchedHost.gameYear);
    strcpy(data[2], searchedHost.location);

    int dayDif = ((searchedHost.gameEndDate.month-searchedHost.gameStartDate.month) * 30) + (searchedHost.gameEndDate.day-searchedHost.gameStartDate.day);
    sprintf(data[3], "%d", dayDif);

    return data;
}

PtSet getDisciplineStatistics(PtMedal medals, int medalsSize, PtMap hosts, char* editionName) {
    int hostSize;
    char* gameSlug;
    bool found = false;
    mapSize(hosts, &hostSize);

    if (medalsSize == 0) {
        printf("Medals array is empty.\n");
        return NULL;
    }
    if (hostSize == 0){
        printf("Hosts map is empty.\n");
        return NULL;
    }

    PtSet set = setCreate();

    if (set == NULL) {
        printf("Failed to create the set.\n");
        return NULL;
    }

    MapKey* keys = mapKeys(hosts);

    for(int i = 0; i<hostSize; i++) {
        Host host;
        mapGet(hosts, keys[i], &host);
        if (strcmp(host.gameName, editionName) == 0) {
            gameSlug = keys[i].text;
            found = true;
        }
    }

    if (!found) {
        printf("No editions found.\n");
        setDestroy(&set);
        return NULL;
    }

    for (int i = 0; i<medalsSize; i++) {
        DisciplineStats dStats;

        if (strcmp(medals[i].game, gameSlug) == 0) {
            strcpy(dStats.disciplineName, medals[i].discipline);
        }
    }

    return set;
}

char** getAthleteInfo(PtMedal medals, int medalsSize, PtList athletes, PtMap hosts, char* athleteID, char* country, int* participations, int* birthYear, int* size) {
    int athletesSize;
    int hostsSize;
    listSize(athletes, &athletesSize);
    mapSize(hosts, &hostsSize);
    
    if (medalsSize == 0) { printf("Medals array is empty.\n"); return NULL; }    
    if (athletesSize == 0) { printf("Athletes list is empty.\n"); return NULL; }
    if (hostsSize == 0) { printf("Hosts map is empty.\n"); return NULL; }

    bool foundAthlete = false;

    for (int i = 0; i < athletesSize; i++) {
        Athlete athlete;
        listGet(athletes, i, &athlete);
        if (strcmp(athlete.athleteID, athleteID) == 0) {
            *participations = athlete.gamesParticipations;
            *birthYear = athlete.athleteBirth;
            foundAthlete = true;
            break; 
        }
    }

    if (!foundAthlete) {
        printf("Athlete %s was not found\n", athleteID);
        return NULL;
    }

    int count = 0;
    char** data = (char**)malloc(0);
    if (data == NULL) {
        printf("Insufficient memory to allocate inicial array.\n");
        return NULL;
    }

    char discipline[50], edition[50], medalType[10];
    MapKey* keys = mapKeys(hosts);

    bool countryFound = false;
    for (int i = 0; i < medalsSize; i++) {
        if (strcmp(medals[i].athleteID, athleteID) == 0) {
            if (!countryFound) {
                strcpy(country, medals[i].country);
                countryFound = true;
            }

            count++;
            char** newData = realloc(data, count * sizeof(char*));
            if (newData == NULL) {
                printf("Insufficient memory to reallocate array.\n");
                
                for (int j = 0; j < count - 1; j++) {
                    free(data[j]);
                }
                free(data);
                return NULL;
            }
            data = newData;

            strcpy(discipline, medals[i].discipline);
            switch (medals[i].medalType) {
                case 'G': strcpy(medalType, "GOLD"); break;
                case 'S': strcpy(medalType, "SILVER"); break;
                case 'B': strcpy(medalType, "BRONZE"); break;
                default: strcpy(medalType, "UNKNOWN"); break;
            }

            for (int j = 0; j < hostsSize; j++) {
                if (strcmp(keys[j].text, medals[i].game) == 0) {
                    Host host;
                    mapGet(hosts, keys[j], &host);
                    strcpy(edition, host.gameName);
                    break; 
                }
            }

            char* piece1 = ": ";
            char* piece2 = " MEDAL; ";

            int totalLength = strlen(edition) + strlen(piece1) + strlen(medalType) + strlen(piece2) + strlen(discipline) + 1;
            char* line = (char*)malloc(totalLength * sizeof(char));
            if (line == NULL) {
                fprintf(stderr, "Memory allocation for line failed\n");
                
                for (int j = 0; j < count; j++) {
                    free(data[j]);
                }
                free(data);
                return NULL;
            }

            strcpy(line, edition);
            strcat(line, piece1);
            strcat(line, medalType);
            strcat(line, piece2);
            strcat(line, discipline);

            data[count - 1] = line;
        }
    }

    if (!countryFound) {
        printf("Athlete %s did not win any medals\n", athleteID);
        for (int j = 0; j < count; j++) {
            free(data[j]);
        }
        free(data);
        return NULL;
    }

    *size = count;
    return data;
}