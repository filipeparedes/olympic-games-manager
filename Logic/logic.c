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
#include "../TopNStats/topnstats.h"

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

PtTopN getTopNCountries(PtMedal medals, int medalsSize, PtMap hosts, PtList athletes, char gameSeason[10], int startYear, int endYear, int* size) {
        int hostsSize, athletesSize;
    mapSize(hosts, &hostsSize);
    listSize(athletes, &athletesSize);
    if (medalsSize == 0) { printf("Medals array is empty.\n"); return NULL; }
    if (hostsSize == 0) { printf("Hosts map is empty.\n"); return NULL; }
    if (athletesSize == 0) { printf("Athletes list is empty.\n"); return NULL; }

    MapKey* keys = mapKeys(hosts);

    char** allowedGames = (char**)malloc(0);
    int gamesCount = 0;

    for (int i = 0; i < hostsSize; i++) {
        Host host;
        if (mapGet(hosts, keys[i], &host) == MAP_OK) {
            if (strcmp(host.season, gameSeason) == 0 &&
                host.gameStartDate.year >= startYear &&
                host.gameEndDate.year <= endYear) {

                gamesCount++;
                char** newAllowedGames = realloc(allowedGames, gamesCount * sizeof(char*));
                if (newAllowedGames == NULL) {
                    printf("Insufficient memory to reallocate array.\n");
                    for (int j = 0; j < gamesCount - 1; j++) {
                        free(allowedGames[j]);
                    }
                    free(allowedGames);
                    return NULL;
                }
                allowedGames = newAllowedGames;
                allowedGames[gamesCount - 1] = strdup(keys[i].text); 
            }
        }
    }

    PtTopN topNList = (TopNStats*)malloc(sizeof(TopNStats));
    if (!topNList) {
        printf("Insufficient memory to allocate TopN list.\n");
        for (int j = 0; j < gamesCount; j++) {
            free(allowedGames[j]);
        }
        free(allowedGames);
        return NULL;
    }

    int topNCount = 0;

    for (int i = 0; i < medalsSize; i++) {
        for (int j = 0; j < gamesCount; j++) {
            if (strcmp(medals[i].game, allowedGames[j]) == 0) {
                int found = 0;
                for (int p = 0; p < topNCount; p++) {
                    if (strcmp(medals[i].country, topNList[p].country) == 0) {
                        found = 1;

                        if (medals[i].medalType == 'G')
                            topNList[p].totalMedals += 3;
                        else if (medals[i].medalType == 'S')
                            topNList[p].totalMedals += 2;
                        else if (medals[i].medalType == 'B')
                            topNList[p].totalMedals += 1;

                        for (int k = 0; k < athletesSize; k++) {
                            Athlete athlete;
                            if (listGet(athletes, k, &athlete) == LIST_OK) {
                                if (strcmp(athlete.athleteID, medals[i].athleteID) == 0) {
                                    topNList[p].avgMedalsEdition = (float)topNList[p].totalMedals / athlete.gamesParticipations;
                                }
                            }
                        }

                        for (int x = 0; x < hostsSize; x++) {
                            Host host;
                            if (strcmp(keys[x].text, medals[i].game) == 0) {
                                if (mapGet(hosts, keys[x], &host) == MAP_OK) {
                                    int days = (host.gameEndDate.month - host.gameStartDate.month) * 30 + (host.gameEndDate.day - host.gameStartDate.day);
                                    topNList[p].totalDays += days;
                                }
                            }
                        }

                        topNList[p].avgMedalsGameDays = (float)topNList[p].totalMedals / topNList[p].totalDays;
                        break;
                    }
                }

                if (!found) {
                    topNCount++;
                    TopNStats* newTopNList = realloc(topNList, topNCount * sizeof(TopNStats));
                    if (newTopNList == NULL) {
                        printf("Insufficient memory to reallocate TopN array.\n");
                        for (int j = 0; j < gamesCount; j++) {
                            free(allowedGames[j]);
                        }
                        free(allowedGames);
                        free(topNList);
                        return NULL;
                    }
                    topNList = newTopNList;

                    TopNStats pivot = { .country = "", .totalMedals = 0, .totalDays = 0, .avgMedalsEdition = 0.0f, .avgMedalsGameDays = 0.0f };
                    strcpy(pivot.country, medals[i].country);

                    if (medals[i].medalType == 'G')
                        pivot.totalMedals += 3;
                    else if (medals[i].medalType == 'S')
                        pivot.totalMedals += 2;
                    else if (medals[i].medalType == 'B')
                        pivot.totalMedals += 1;

                    for (int k = 0; k < athletesSize; k++) {
                        Athlete athlete;
                        if (listGet(athletes, k, &athlete) == LIST_OK) {
                            if (strcmp(athlete.athleteID, medals[i].athleteID) == 0) {
                                pivot.avgMedalsEdition = (float)pivot.totalMedals / athlete.gamesParticipations;
                            }
                        }
                    }

                    for (int x = 0; x < hostsSize; x++) {
                        Host host;
                        if (strcmp(keys[x].text, medals[i].game) == 0) {
                            if (mapGet(hosts, keys[x], &host) == MAP_OK) {
                                int days = (host.gameEndDate.month - host.gameStartDate.month) * 30 + (host.gameEndDate.day - host.gameStartDate.day);
                                pivot.totalDays += days;
                            }
                        }
                    }

                    pivot.avgMedalsGameDays = (float)pivot.totalMedals / pivot.totalDays;

                    topNList[topNCount - 1] = pivot;
                }
            }
        }
    }

    for (int j = 0; j < gamesCount; j++) {
        free(allowedGames[j]);
    }
    free(allowedGames);

    if (topNCount == 0) {
        printf("No data found for the requested period.\n");
        return NULL;
    }

    *size = topNCount;

    return topNList;
}
