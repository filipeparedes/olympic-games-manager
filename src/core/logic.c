/**
 * @file logic.c
 *
 * @brief Contains implementation for logic.h
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.2.0
 * @date 2026-04-21
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

#include "core/logic.h"
#include "adt/map_elem.h"
#include "adt/map.h"
#include "adt/set.h"
#include "adt/set_elem.h"
#include "adt/list.h"
#include "adt/list_elem.h"
#include "domain/medal.h"
#include "domain/discipline_stats.h"
#include "domain/top_n_stats.h"

#define MAX_COUNTRIES 100
#define MAX_DISCIPLINES 60
 
typedef struct {
    char discipline[MAX_DISCIPLINE_SIZE];
 
    /* country medal counts */
    char   countries[MAX_COUNTRIES][MAX_COUNTRY_SIZE];
    int    country_counts[MAX_COUNTRIES];
    int    country_count;
 
    /* gender counts */
    int    women_medals;
    int    total_medals;
} discipline_agg_t;

set_t *get_discipline_statistics(medal_t *medals, int medals_size, map_t *hosts, char *edition_name) {
    int host_size;
    bool found = false;
    char game_slug[100] = {0};
 
    map_size(hosts, &host_size);
 
    if (medals_size == 0) { printf("Medals array is empty.\n");  return NULL; }
    if (host_size == 0)   { printf("Hosts map is empty.\n");     return NULL; }
 
    set_t *set = set_create();
    if (set == NULL) { printf("Failed to create the set.\n"); return NULL; }
 
    /* --- Find the slug for the requested edition --- */
    map_key_t *keys = map_keys(hosts);
    for (int i = 0; i < host_size; i++) {
        host_t host;
        map_get(hosts, keys[i], &host);
        if (strcmp(host.game_name, edition_name) == 0) {
            strncpy(game_slug, keys[i].text, sizeof(game_slug) - 1);
            found = true;
            break;
        }
    }
 
    if (!found) {
        printf("No edition found: %s\n", edition_name);
        set_destroy(&set);
        return NULL;
    }
 
    /* --- Aggregate per discipline --- */
    discipline_agg_t *aggs = (discipline_agg_t *)calloc(MAX_DISCIPLINES, sizeof(discipline_agg_t));
    if (aggs == NULL) {
        printf("Insufficient memory for aggregation.\n");
        set_destroy(&set);
        return NULL;
    }
    int agg_count = 0;
 
    for (int i = 0; i < medals_size; i++) {
        if (strcmp(medals[i].game, game_slug) != 0) continue;
 
        /* Find or create aggregation entry for this discipline */
        int d = -1;
        for (int k = 0; k < agg_count; k++) {
            if (strcmp(aggs[k].discipline, medals[i].discipline) == 0) {
                d = k;
                break;
            }
        }
        if (d == -1) {
            if (agg_count >= MAX_DISCIPLINES) continue; /* safety cap */
            d = agg_count++;
            strncpy(aggs[d].discipline, medals[i].discipline, MAX_DISCIPLINE_SIZE - 1);
        }
 
        aggs[d].total_medals++;
 
        /* Track gender */
        if (medals[i].gender == 'W') aggs[d].women_medals++;
 
        /* Track country medal count */
        int c = -1;
        for (int k = 0; k < aggs[d].country_count; k++) {
            if (strcmp(aggs[d].countries[k], medals[i].country) == 0) {
                c = k;
                break;
            }
        }
        if (c == -1 && aggs[d].country_count < MAX_COUNTRIES) {
            c = aggs[d].country_count++;
            strncpy(aggs[d].countries[c], medals[i].country, MAX_COUNTRY_SIZE - 1);
            aggs[d].country_counts[c] = 0;
        }
        if (c != -1) aggs[d].country_counts[c]++;
    }
 
    /* --- Build discipline_stats_t entries and insert into set --- */
    for (int d = 0; d < agg_count; d++) {
        discipline_stats_t dstats = {0};
 
        strncpy(dstats.discipline_name, aggs[d].discipline, MAX_DISCIPLINE_SIZE - 1);
 
        /* Find top country */
        int best = -1, best_count = 0;
        for (int c = 0; c < aggs[d].country_count; c++) {
            if (aggs[d].country_counts[c] > best_count) {
                best_count = aggs[d].country_counts[c];
                best = c;
            }
        }
        if (best != -1)
            strncpy(dstats.top_medals_country, aggs[d].countries[best], MAX_COUNTRY_SIZE - 1);
 
        /* Women ratio */
        dstats.women_ratio = (aggs[d].total_medals > 0)
            ? (float)aggs[d].women_medals / (float)aggs[d].total_medals
            : 0.0f;
 
        set_add(set, dstats);
    }
 
    free(aggs);
    return set;
}

list_t *filter_list_by_participations(list_t *athletes, int participations){

    int org_list_size;
    list_size(athletes, &org_list_size);
    if (org_list_size == 0) {
        printf("The original list is empty.\n");
        return NULL;
    }

    list_t *filtered_list = list_create();
    if (filtered_list == NULL){
        printf("Failed to create a filtered list.\n");
        return NULL;
    }

    for (int i = 0, j=0; i < org_list_size; i++) {
        athlete_t athlete;

        if (list_get(athletes, i, &athlete) == LIST_OK) {
            if (athlete.games_participations >= participations){
                list_add(filtered_list, j++, athlete);
            }
        }
    }

    return filtered_list;
}

list_t *filter_list_by_first_year(list_t *athletes, char *first_year){

    int org_list_size;
    list_size(athletes, &org_list_size);
    if (org_list_size == 0) {
        printf("The original list is empty.\n");
        return NULL;
    }

    list_t *filtered_list = list_create();
    if (filtered_list == NULL){
        printf("Failed to create filtered list.\n");
        return NULL;
    }

    for (int i = 0, j=0; i < org_list_size; i++) {
        athlete_t athlete;

        if (list_get(athletes, i, &athlete) == LIST_OK) {
            int len = strlen(athlete.first_game);
            if (len >= 4) { 
                char* year = athlete.first_game + (len - 4); //Extracts the last four digits of the string 
                if (strcmp(year, first_year) == 0){
                    list_add(filtered_list, j++, athlete);
                }
            }
        }
    }
    return filtered_list;
}

char **get_host_data(map_t *hosts, char *edition_name){

    int org_map_size;
    map_size(hosts, &org_map_size);

    if (org_map_size == 0){
        printf("The original map is empty.\n");
        return NULL;
    }

    map_key_t *keys = map_keys(hosts);

    char **data = (char**)malloc(4 * sizeof(char*));

    if (data == NULL) {
        printf("Failed to create the data array.\n");
        return NULL;
    }

    //Alocate memory for strings inside the array
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

    host_t searched_host;
    bool found = false;
    
    for (int i = 0; i<org_map_size; i++) {
        host_t host;
        map_get(hosts, keys[i], &host);
        if (strcmp(host.game_name,edition_name) == 0){
            searched_host = host;
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

    int game_name_len = strlen(searched_host.game_name);
    if (game_name_len > 5) {
        strncpy(data[0], searched_host.game_name, game_name_len-4);
        data[0][game_name_len-5] = '\0';
    } 
    else strcpy(data[0], "");
    
    sprintf(data[1], "%d", searched_host.game_year);
    strcpy(data[2], searched_host.location);

    int day_dif = ((searched_host.game_end_date.month-searched_host.game_start_date.month) * 30) + (searched_host.game_end_date.day-searched_host.game_start_date.day);
    sprintf(data[3], "%d", day_dif);

    return data;
}

char **get_athlete_info(medal_t *medals, int medals_size, list_t *athletes, map_t *hosts, char *athlete_id, char *country, int *participations, int *birthYear, int *size) {

    int athletes_size;
    int hosts_size;
    list_size(athletes, &athletes_size);
    map_size(hosts, &hosts_size);
    
    if (medals_size == 0) { printf("Medals array is empty.\n"); return NULL; }    
    if (athletes_size == 0) { printf("Athletes list is empty.\n"); return NULL; }
    if (hosts_size == 0) { printf("Hosts map is empty.\n"); return NULL; }

    bool found_athlete = false;

    for (int i = 0; i < athletes_size; i++) {
        athlete_t athlete;
        list_get(athletes, i, &athlete);
        if (strcmp(athlete.athlete_id, athlete_id) == 0) {
            *participations = athlete.games_participations;
            *birthYear = athlete.athlete_birth;
            found_athlete = true;
            break; 
        }
    }

    if (!found_athlete) {
        printf("Athlete %s was not found\n", athlete_id);
        return NULL;
    }

    int count = 0;
    char **data = (char**)malloc(0);
    if (data == NULL) {
        printf("Insufficient memory to allocate inicial array.\n");
        return NULL;
    }

    char discipline[50], edition[50], medal_type[10];
    map_key_t* keys = map_keys(hosts);

    bool country_found = false;
    for (int i = 0; i < medals_size; i++) {
        if (strcmp(medals[i].athlete_id, athlete_id) == 0) {
            if (!country_found) {
                strcpy(country, medals[i].country);
                country_found = true;
            }

            count++;
            char **new_data = realloc(data, count * sizeof(char*));
            if (new_data == NULL) {
                printf("Insufficient memory to reallocate array.\n");
                
                for (int j = 0; j < count - 1; j++) {
                    free(data[j]);
                }
                free(data);
                return NULL;
            }
            data = new_data;

            strcpy(discipline, medals[i].discipline);
            switch (medals[i].medal_type) {
                case 'G': strcpy(medal_type, "GOLD"); break;
                case 'S': strcpy(medal_type, "SILVER"); break;
                case 'B': strcpy(medal_type, "BRONZE"); break;
                default: strcpy(medal_type, "UNKNOWN"); break;
            }

            for (int j = 0; j < hosts_size; j++) {
                if (strcmp(keys[j].text, medals[i].game) == 0) {
                    host_t host;
                    map_get(hosts, keys[j], &host);
                    strcpy(edition, host.game_name);
                    break; 
                }
            }

            char* piece1 = ": ";
            char* piece2 = " MEDAL; ";

            int total_length = strlen(edition) + strlen(piece1) + strlen(medal_type) + strlen(piece2) + strlen(discipline) + 1;
            char* line = (char*)malloc(total_length * sizeof(char));
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
            strcat(line, medal_type);
            strcat(line, piece2);
            strcat(line, discipline);

            data[count - 1] = line;
        }
    }

    if (!country_found) {
        printf("Athlete %s did not win any medals\n", athlete_id);
        for (int j = 0; j < count; j++) {
            free(data[j]);
        }
        free(data);
        return NULL;
    }

    *size = count;
    return data;
}

top_n_stats_t *get_top_n_countries(medal_t *medals, int medals_size, map_t *hosts, list_t *athletes, char game_season[10], int start_year, int end_year, int *size) {
    int hosts_size, athletes_size;
    map_size(hosts, &hosts_size);
    list_size(athletes, &athletes_size);
    if (medals_size == 0) { printf("Medals array is empty.\n"); return NULL; }
    if (hosts_size == 0) { printf("Hosts map is empty.\n"); return NULL; }
    if (athletes_size == 0) { printf("Athletes list is empty.\n"); return NULL; }

    map_key_t *keys = map_keys(hosts);

    char **allowed_games = (char**)malloc(0);
    int games_count = 0;

    for (int i = 0; i < hosts_size; i++) {
        host_t host;
        if (map_get(hosts, keys[i], &host) == MAP_OK) {
            if (strcmp(host.season, game_season) == 0 &&
                host.game_start_date.year >= start_year &&
                host.game_end_date.year <= end_year) {

                games_count++;
                char **new_allowed_games = realloc(allowed_games, games_count * sizeof(char*));
                if (new_allowed_games == NULL) {
                    printf("Insufficient memory to reallocate array.\n");
                    for (int j = 0; j < games_count - 1; j++) {
                        free(allowed_games[j]);
                    }
                    free(allowed_games);
                    return NULL;
                }
                allowed_games = new_allowed_games;
                allowed_games[games_count - 1] = strdup(keys[i].text); 
            }
        }
    }

    top_n_stats_t *top_n_list = (top_n_stats_t*)malloc(sizeof(top_n_stats_t));
    if (!top_n_list) {
        printf("Insufficient memory to allocate TopN list.\n");
        for (int j = 0; j < games_count; j++) {
            free(allowed_games[j]);
        }
        free(allowed_games);
        return NULL;
    }

    int top_n_count = 0;

    for (int i = 0; i < medals_size; i++) {
        for (int j = 0; j < games_count; j++) {
            if (strcmp(medals[i].game, allowed_games[j]) == 0) {
                int found = 0;
                for (int p = 0; p < top_n_count; p++) {
                    if (strcmp(medals[i].country, top_n_list[p].country) == 0) {
                        found = 1;

                        if (medals[i].medal_type == 'G')
                            top_n_list[p].total_medals += 3;
                        else if (medals[i].medal_type == 'S')
                            top_n_list[p].total_medals += 2;
                        else if (medals[i].medal_type == 'B')
                            top_n_list[p].total_medals += 1;

                        for (int k = 0; k < athletes_size; k++) {
                            athlete_t athlete;
                            if (list_get(athletes, k, &athlete) == LIST_OK) {
                                if (strcmp(athlete.athlete_id, medals[i].athlete_id) == 0) {
                                    top_n_list[p].avg_medals_edition = (float)top_n_list[p].total_medals / athlete.games_participations;
                                }
                            }
                        }

                        for (int x = 0; x < hosts_size; x++) {
                            host_t host;
                            if (strcmp(keys[x].text, medals[i].game) == 0) {
                                if (map_get(hosts, keys[x], &host) == MAP_OK) {
                                    int days = (host.game_end_date.month - host.game_start_date.month) * 30 + (host.game_end_date.day - host.game_start_date.day);
                                    top_n_list[p].total_days += days;
                                }
                            }
                        }

                        top_n_list[p].avg_medals_game_days = (float)top_n_list[p].total_medals / top_n_list[p].total_days;
                        break;
                    }
                }

                if (!found) {
                    top_n_count++;
                    top_n_stats_t *new_top_n_list = realloc(top_n_list, top_n_count * sizeof(top_n_stats_t));
                    if (new_top_n_list == NULL) {
                        printf("Insufficient memory to reallocate TopN array.\n");
                        for (int j = 0; j < games_count; j++) {
                            free(allowed_games[j]);
                        }
                        free(allowed_games);
                        free(top_n_list);
                        return NULL;
                    }
                    top_n_list = new_top_n_list;

                    top_n_stats_t pivot = { .country = "", .total_medals = 0, .total_days = 0, .avg_medals_edition = 0.0f, .avg_medals_game_days = 0.0f };
                    strcpy(pivot.country, medals[i].country);

                    if (medals[i].medal_type == 'G')
                        pivot.total_medals += 3;
                    else if (medals[i].medal_type == 'S')
                        pivot.total_medals += 2;
                    else if (medals[i].medal_type == 'B')
                        pivot.total_medals += 1;

                    for (int k = 0; k < athletes_size; k++) {
                        athlete_t athlete;
                        if (list_get(athletes, k, &athlete) == LIST_OK) {
                            if (strcmp(athlete.athlete_id, medals[i].athlete_id) == 0) {
                                pivot.avg_medals_edition = (float)pivot.total_medals / athlete.games_participations;
                            }
                        }
                    }

                    for (int x = 0; x < hosts_size; x++) {
                        host_t host;
                        if (strcmp(keys[x].text, medals[i].game) == 0) {
                            if (map_get(hosts, keys[x], &host) == MAP_OK) {
                                int days = (host.game_end_date.month - host.game_start_date.month) * 30 + (host.game_end_date.day - host.game_start_date.day);
                                pivot.total_days += days;
                            }
                        }
                    }

                    pivot.avg_medals_game_days = (float)pivot.total_medals / pivot.total_days;

                    top_n_list[top_n_count - 1] = pivot;
                }
            }
        }
    }

    for (int j = 0; j < games_count; j++) {
        free(allowed_games[j]);
    }
    free(allowed_games);

    if (top_n_count == 0) {
        printf("No data found for the requested period.\n");
        return NULL;
    }

    *size = top_n_count;

    return top_n_list;
}

void get_medals_won(medal_t *medals, int medals_size, map_t *hosts, char *country, int start_year, char *season) {
    int hosts_size;
    map_size(hosts, &hosts_size);
 
    if (medals_size == 0) { printf("Medals array is empty.\n"); return; }
    if (hosts_size == 0)  { printf("Hosts map is empty.\n");   return; }
 
    map_key_t *keys = map_keys(hosts);
 
    int gold = 0, silver = 0, bronze = 0;
    int found = 0;
 
    printf("\nMedals won by %s from %d (%s):\n", country, start_year, season);
    printf("%-40s %-15s %-10s\n", "Edition", "Discipline", "Medal");
    printf("%-40s %-15s %-10s\n", "-------", "----------", "-----");
 
    for (int i = 0; i < medals_size; i++) {
        if (strcmp(medals[i].country, country) != 0) continue;
 
        // Resolve host to check year and season
        host_t host;
        bool host_found = false;
 
        for (int j = 0; j < hosts_size; j++) {
            if (strcmp(keys[j].text, medals[i].game) == 0) {
                if (map_get(hosts, keys[j], &host) == MAP_OK) {
                    host_found = true;
                    break;
                }
            }
        }
 
        if (!host_found) continue;
        if (strcmp(host.season, season) != 0) continue;
        if (host.game_start_date.year < start_year) continue;
 
        char medal_str[10];
        switch (medals[i].medal_type) {
            case 'G': strcpy(medal_str, "GOLD");   gold++;   break;
            case 'S': strcpy(medal_str, "SILVER"); silver++; break;
            case 'B': strcpy(medal_str, "BRONZE"); bronze++; break;
            default:  strcpy(medal_str, "?");                break;
        }
 
        printf("%-40s %-15s %-10s\n", host.game_name, medals[i].discipline, medal_str);
        found++;
    }
 
    if (found == 0) {
        printf("No medals found.\n");
        return;
    }
 
    printf("\nTotal: %d medal(s) — Gold: %d | Silver: %d | Bronze: %d\n",
           gold + silver + bronze, gold, silver, bronze);
}