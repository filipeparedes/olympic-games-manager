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
            gameSlug = host.gameName;
            found = true;
        }
    }

    if (!found) {
        printf("No editions found.\n");
        return NULL;
    }

    for (int i = 0; i<medalsSize; i++) {
        if (strcmp(medals[i].game, gameSlug) == 0) {
            setAdd(set, medals[i].discipline);
        }
    }

    return set;
}