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

PtMap filterMapByParticipations(PtMap athletes, int participations){

    PtMap filteredMap = mapCreate();
    if (filteredMap == NULL){
        printf("Failed to create filtered map.\n");
        return NULL;
    }

    int orgMapSize;
    mapSize(athletes, &orgMapSize);
    if (orgMapSize == 0) {
        printf("The original map is empty.\n");
        return NULL;
    }

    StringWrap* keys = mapKeys(athletes);

    for (int i = 0; i < orgMapSize; i++) {
        Athlete athlete;

        if (mapGet(athletes, keys[i], &athlete) == MAP_OK) {
            if (athlete.gamesParticipations >= participations){
                mapPut(filteredMap, keys[i], athlete);
            }
        }
    }

    free(keys);
    return filteredMap;
}

PtMap filterMapByFirstYear(PtMap athletes, char* firstYear){

    PtMap filteredMap = mapCreate();
    if (filteredMap == NULL){
        printf("Failed to create filtered map.\n");
        return NULL;
    }

    int orgMapSize;
    mapSize(athletes, &orgMapSize);
    if (orgMapSize == 0) {
        printf("The original map is empty.\n");
        return NULL;
    }

    StringWrap* keys = mapKeys(athletes);
    if (keys == NULL) {
        printf("Failed to retrieve keys from the map.\n");
        return NULL;
    }

    for (int i = 0; i < orgMapSize; i++) {
        Athlete athlete;

        if (mapGet(athletes, keys[i], &athlete) == MAP_OK) {
            int len = strlen(athlete.firstGame);
            if (len >= 4) { 
                char* year = athlete.firstGame + (len - 4); //Extracts the last four digits of the string "athlete.firstGame"
                if (strcmp(year, firstYear) == 0){
                    mapPut(filteredMap, keys[i], athlete);
                }
            }
        }
    }

    free(keys);
    return filteredMap;
}

char** getHostData(PtHost host, int hostSize, char* editionName) {

    if (hostSize == 0){
        printf("The original array is empty.\n");
        return NULL;
    }

    char** data = (char**)malloc(4 * sizeof(char*));

    if (data == NULL) {
        printf("Failed to create the data array.\n");
        return NULL;
    }

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
    
    for (int i = 0; i<hostSize; i++) {
        if (strcmp(host[i].gameName,editionName) == 0){
            searchedHost = host[i];
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