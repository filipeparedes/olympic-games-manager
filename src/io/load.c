/**
 * @file load.c
 * 
 * @brief Implementation of functions to load data from medals, athletes, and hosts CSV files.
 * 
 * This source file contains the implementation of functions for reading and parsing data 
 * from medals.csv, athletes.csv, and hosts.csv files, and storing the data into appropriate 
 * data structures such as lists and maps.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2026
 * 
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "io/load.h"
#include "utils/date.h"
#include "domain/medal.h"

int import_medals(medal_t *array, int *size){
    FILE *file = fopen("data/medals.csv", "r");
    if (file == NULL) return FILE_NOT_FOUND;
    if (array == NULL) return ARRAY_NULL;

    int count = 0;
    char line[FILE_LINE_SIZE];

    while (fgets(line, FILE_LINE_SIZE, file) != NULL) {
        if (count == 0) {count++; continue;}
        line[strlen(line)] = '\0';

        char **split_str = split_string(line, 10, ";");
        if (split_str == NULL) continue;

        medal_t medal;
        if(split_str[0] != NULL) strcpy(medal.discipline, split_str[0]);
        if(split_str[1] != NULL) strcpy(medal.game, split_str[1]);
        if(split_str[2] != NULL) strcpy(medal.event_title, split_str[2]);
        if(split_str[3] != NULL) medal.gender = split_str[3][0];
        if(split_str[4] != NULL) medal.medal_type = split_str[4][0];
        if(split_str[5] != NULL) medal.participant_type = split_str[5][0];
        if(split_str[7] != NULL) strcpy(medal.athlete_id, split_str[7]);
        if(split_str[8] != NULL) strcpy(medal.country, split_str[8]);
        if(split_str[9] != NULL) strncpy(medal.country_code, split_str[9], 3);

        array[count-1] = medal;
        count++;
        free(split_str);
    }

    *size = count-1;
    fclose(file);

    return LOAD_OK;
}

int import_athletes(list_t *list, int *size){
    FILE *file = fopen("data/athletes.csv", "r");
    if (file == NULL) return FILE_NOT_FOUND;
    if (list == NULL) return LIST_NULL;

    list_clear(list);

    int count = 0;
    char line[FILE_LINE_SIZE];

    while (fgets(line, FILE_LINE_SIZE, file) != NULL) {
        if (count == 0) {count++; continue;}
        line[strlen(line)] = '\0';

        char** split_str = split_string(line, 5, ";");
        if (split_str == NULL) continue;

        athlete_t athlete;
        if(split_str[0] != NULL) strcpy(athlete.athlete_id, split_str[0]);
        if(split_str[1] != NULL) strcpy(athlete.athlete_name, split_str[1]);
        if(split_str[2] != NULL) athlete.games_participations = atoi(split_str[2]);
        if(split_str[3] != NULL) strcpy(athlete.first_game, split_str[3]);
        if(split_str[4] != NULL) athlete.athlete_birth = atoi(split_str[4]);

        list_add(list, count-1, athlete);
        free(split_str);
    }

    listSize(list, size);

    fclose(file);
    return LOAD_OK;

}

int import_hosts(map_t *map, int* size){
    FILE* file = fopen("data/hosts.csv", "r");
    if (file == NULL) return FILE_NOT_FOUND;
    if (map == NULL) return MAP_NULL;

    map_clear(map);

    bool first_line = true;
    char line[FILE_LINE_SIZE];

    while(fgets(line, FILE_LINE_SIZE, file) != NULL){
        if (first_line) {
            first_line = false; 
            continue;
        }
        line[strlen(line)] = '\0';

        char **split_str = split_string(line, 7, ";");
        if (split_str == NULL) continue;

        host_t host;
        string_wrap_t str_wrap;
        if(split_str[0] != NULL) str_wrap = string_wrap_create(split_str[0]);
        if(split_str[1] != NULL) stringToDate(split_str[1], &host.game_end_date);
        if(split_str[2] != NULL) stringToDate(split_str[2], &host.game_start_date);
        if(split_str[3] != NULL) strcpy(host.location, split_str[3]);
        if(split_str[4] != NULL) strcpy(host.game_name, split_str[4]);
        if(split_str[5] != NULL) strcpy(host.season, split_str[5]);
        if(split_str[6] != NULL) host.game_year = atoi(split_str[6]);

        mapPut(map, str_wrap, host);

        free(split_str);
    }
    mapSize(map, size);

    fclose(file);
    return LOAD_OK;
}

int count_file_lines(FILE *file) {
    int count = 0;
    char line[FILE_LINE_SIZE];

    if (file == NULL) return FILE_NOT_FOUND;

    while (fgets(line, FILE_LINE_SIZE, file) != NULL) {
        line[strlen(line)] = '\0';
        count++;
    }

    return count-1;
}
