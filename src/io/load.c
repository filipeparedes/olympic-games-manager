/**
 * @file load.c
 * @brief Implementation of functions to load data from medals, athletes, and hosts CSV files.
 * 
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * 
 * This source file contains the implementation of functions for reading and parsing data 
 * from medals.csv, athletes.csv, and hosts.csv files, and storing the data into appropriate 
 * data structures such as lists and maps.
 * 
 * @version 0.3
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "io/load.h"
#include "utils/date.h"
#include "domain/medal.h"

int importMedals(PtMedal array, int* size){
    FILE* file = fopen("data/medals.csv", "r");
    if (file == NULL) return FILE_NOT_FOUND;
    if (array == NULL) return ARRAY_NULL;

    int count = 0;
    char line[FILE_LINE_SIZE];

    while (fgets(line, FILE_LINE_SIZE, file) != NULL) {
        if (count == 0) {count++; continue;}
        line[strlen(line)] = '\0';

        char** splitStr = splitString(line, 10, ";");
        if (splitStr == NULL) continue;

        Medal medal;
        if(splitStr[0] != NULL) strcpy(medal.discipline, splitStr[0]);
        if(splitStr[1] != NULL) strcpy(medal.game, splitStr[1]);
        if(splitStr[2] != NULL) strcpy(medal.eventTitle, splitStr[2]);
        if(splitStr[3] != NULL) medal.gender = splitStr[3][0];
        if(splitStr[4] != NULL) medal.medalType = splitStr[4][0];
        if(splitStr[5] != NULL) medal.participantType = splitStr[5][0];
        if(splitStr[7] != NULL) strcpy(medal.athleteID, splitStr[7]);
        if(splitStr[8] != NULL) strcpy(medal.country, splitStr[8]);
        if(splitStr[9] != NULL) strncpy(medal.countryCode, splitStr[9], 3);

        array[count-1] = medal;
        count++;
        free(splitStr);
    }

    *size = count-1;
    fclose(file);

    return LOAD_OK;
}

int importAthletes(PtList list, int* size){
    FILE* file = fopen("data/athletes.csv", "r");
    if (file == NULL) return FILE_NOT_FOUND;
    if (list == NULL) return LIST_NULL;

    listClear(list);

    int count = 0;
    char line[FILE_LINE_SIZE];

    while (fgets(line, FILE_LINE_SIZE, file) != NULL) {
        if (count == 0) {count++; continue;}
        line[strlen(line)] = '\0';

        char** splitStr = splitString(line, 5, ";");
        if (splitStr == NULL) continue;

        Athlete athlete;
        if(splitStr[0] != NULL){strcpy(athlete.athleteID, splitStr[0]);}
        if(splitStr[1] != NULL) strcpy(athlete.athleteName, splitStr[1]);
        if(splitStr[2] != NULL) athlete.gamesParticipations = atoi(splitStr[2]);
        if(splitStr[3] != NULL) strcpy(athlete.firstGame, splitStr[3]);
        if(splitStr[4] != NULL) athlete.athleteBirth = atoi(splitStr[4]);

        listAdd(list, count-1, athlete);
        free(splitStr);
    }

    listSize(list, size);

    fclose(file);
    return LOAD_OK;

}

int importHosts(PtMap map, int* size){
    FILE* file = fopen("data/hosts.csv", "r");
    if (file == NULL) return FILE_NOT_FOUND;
    if (map == NULL) return MAP_NULL;

    mapClear(map);

    bool firstLine = true;
    char line[FILE_LINE_SIZE];

    while(fgets(line, FILE_LINE_SIZE, file) != NULL){
        if (firstLine) {firstLine = false; continue;}
        line[strlen(line)] = '\0';

        char** splitStr = splitString(line, 7, ";");
        if (splitStr == NULL) continue;

        Host host;
        StringWrap strWrap;
        if(splitStr[0] != NULL){strWrap = stringWrapCreate(splitStr[0]);}
        if(splitStr[1] != NULL) stringToDate(splitStr[1], &host.gameEndDate);
        if(splitStr[2] != NULL) stringToDate(splitStr[2], &host.gameStartDate);
        if(splitStr[3] != NULL) strcpy(host.location, splitStr[3]);
        if(splitStr[4] != NULL) strcpy(host.gameName, splitStr[4]);
        if(splitStr[5] != NULL) strcpy(host.season, splitStr[5]);
        if(splitStr[6] != NULL) host.gameYear = atoi(splitStr[6]);

        mapPut(map, strWrap, host);

        free(splitStr);
    }
    mapSize(map, size);

    fclose(file);
    return LOAD_OK;
}

int countFileLines(FILE* file) {
    int count = 0;
    char line[FILE_LINE_SIZE];

    if (file == NULL) return FILE_NOT_FOUND;

    while (fgets(line, FILE_LINE_SIZE, file) != NULL) {
        line[strlen(line)] = '\0';
        count++;
    }

    return count-1;
}
