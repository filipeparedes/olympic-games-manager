/**
 * @file main.c
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * @brief Main file of the program. Contains its entry point. Represents a command prompt.
 * 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h> 
#include <stdlib.h>

#include "io/input.h"
#include "domain/host.h"
#include "domain/medal.h"
#include "domain/athlete.h"
#include "utils/stringWrap.h"
#include "adt/map.h"
#include "adt/list.h"
#include "io/load.h"
#include "io/listings.h"
#include "core/logic.h"

#define ARRAY_NO_MEMORY 1

#define MAX_COMMAND_LENGTH 25
#define MAX_LINE_LENGTH 1000

int main() {

    bool quit = false;
    char command[MAX_COMMAND_LENGTH];

    PtList athletesList = listCreate();
    PtMap hostsMap = mapCreate();

    FILE* medalsFile = fopen("data/medals.csv", "r");
    if (medalsFile == NULL) return FILE_NOT_FOUND;
    PtMedal medalsArray = (Medal*) malloc(sizeof(Medal)* countFileLines(medalsFile));
    fclose(medalsFile);

    if (athletesList == NULL) return LIST_NO_MEMORY;
    if (hostsMap == NULL) return MAP_NO_MEMORY;
    if (medalsArray == NULL) return ARRAY_NO_MEMORY;

    int hostsSize = 0;
    int athletesSize = 0;
    int medalsSize = 0;

    do {
        printf("\nbash@Projeto-ATAD:~$ ");
        readString(command, MAX_COMMAND_LENGTH);

        //Makes every character in the command lowercase
        for (int i = 0; command[i]; i++) {
            command[i] = tolower(command[i]);
        }

        if (strcmp(command, "load_a") == 0) {
            int ret = importAthletes(athletesList, &athletesSize);

            if(ret == LOAD_OK) printf("%d athlete records imported.\n", athletesSize);
            else if (ret == FILE_NOT_FOUND) printf("File not found.\n");
            else if (ret == MAP_NULL) printf("Invalid map pointer.");
        }   
        else if (strcmp(command, "load_m") == 0) {
            int ret = importMedals(medalsArray, &medalsSize);

            if(ret == LOAD_OK) printf("%d medal records imported.\n", medalsSize);
            else if (ret == FILE_NOT_FOUND) printf("File not found.\n");
            else if (ret == MAP_NULL) printf("Invalid map pointer.");
        }
        else if (strcmp(command, "load_h") == 0) {
            int ret = importHosts(hostsMap, &hostsSize);

            if(ret == LOAD_OK) printf("%d host records imported.\n", hostsSize);
            else if (ret == FILE_NOT_FOUND) printf("File not found.\n");
            else if (ret == MAP_NULL) printf("Invalid map pointer.");
        }
        else if (strcmp(command, "clear") == 0) {
            if (hostsMap != NULL) {
                mapDestroy(&hostsMap);
                hostsMap = NULL;
            }
            if (athletesList != NULL) {
                listDestroy(&athletesList);
                athletesList = NULL;
            }
            if (medalsArray != NULL) {
                free(medalsArray);
                medalsArray = NULL;
            } 

            printf("Records deleted from Athletes (%d) | Medals (%d) | Hosts (%d)\n", athletesSize, medalsSize, hostsSize);

            hostsSize = 0;
            athletesSize = 0;
            medalsSize = 0;
        }
        else if (strcmp(command, "show_all") == 0) {
            paginate(athletesList);
        }
        else if (strcmp(command, "show_participations") == 0) {
            int participations;
            printf("Insert number of participations: ");
            scanf("%d", &participations);

            PtList filteredList = filterListByParticipations(athletesList, participations);
            int filteredListSize;
            listSize(filteredList, &filteredListSize);
            if (filteredListSize == 0) printf("No athletes found with at least %d participations.\n", participations);
            else {
                paginate(filteredList);
            }
        }
        else if (strcmp(command, "show_first") == 0) {
            char firstYear[5];
            printf("Insert the first participation's year (YYYY): ");
            scanf("%s", firstYear);

            PtList filteredList = filterListByFirstYear(athletesList, firstYear);
            int filteredListSize;
            listSize(filteredList, &filteredListSize);
            if (filteredListSize == 0) printf("No athletes whose first participation was at %s\n", firstYear);
            else {
                paginate(filteredList);
            }

        }
        else if (strcmp(command, "show_host") == 0) {
            char editionName[50];
            printf("Insert an edition name (e.g. 'Montreal 1976'): ");
            readString(editionName, 50);

            char** hostData = getHostData(hostsMap, editionName);

            printHostDetails(hostData);

            free(hostData);
            hostData = NULL;
        }
        else if (strcmp(command, "discipline_statistics") == 0) {
            char editionName[50];
            printf("Insert an edition name (e.g. 'Sydney 2000'): ");
            readString(editionName, 50);

            PtSet set = getDisciplineStatistics(medalsArray, medalsSize, hostsMap, editionName);
            int size;
            setSize(set, &size);

            if(size > 0) paginateSet(set);
        }
        else if (strcmp(command, "athlete_info") == 0) {
            char athlete[50];
            printf("Insert an athleteID: ");
            readString(athlete, 50);

            int participations, birthYear, medalsStatsSize;
            char country[30];

            char** medalsStatistics = getAthleteInfo(medalsArray, medalsSize, athletesList, hostsMap, athlete, country, &participations, &birthYear, &medalsStatsSize);

            if (medalsStatistics != NULL)
            printAthleteInfo(medalsStatistics, medalsStatsSize, country, athlete, participations, birthYear);
        }
        else if (strcmp(command, "topn") == 0) {
            int startYear, endYear, n, topNSize;
            char gameSeason[10];
            printf("Insert a game season (Winter/Summer): ");
            readString(gameSeason, 10);
            printf("Insert the starting year (YYYY): ");
            readInteger(&startYear);
            printf("Insert the ending year (YYYY): ");
            readInteger(&endYear);
            printf("Insert the amount of results to show up: ");
            readInteger(&n);

            PtTopN topNList = getTopNCountries(medalsArray, medalsSize, hostsMap, athletesList, gameSeason, startYear, endYear, &topNSize);

            if (topNList != NULL)
            printTopN(topNList, n, topNSize);
        }
        else if (strcmp(command, "medals_won") == 0) {
            char country[50], gameSeason[10];
            int year;
            printf("Insert the country: ");
            readString(country, 50);
            printf("Insert the starting year (YYYY): ");
            readInteger(&year);
            printf("Insert a game season (Winter/Summer): ");
            readString(gameSeason, 10);
        }
        else if (strcmp(command, "quit") == 0) {
            quit = true;
        }
        else {
            printf("Unknown Command\n");
        }
    } while (!quit);

    if (athletesList != NULL) listDestroy(&athletesList); 
    if (hostsMap != NULL) mapDestroy(&hostsMap);
    if (medalsArray != NULL) free(medalsArray);

    return EXIT_SUCCESS;
}