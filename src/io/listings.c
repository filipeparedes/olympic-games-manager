/**
 * @file listings.c
 * 
 * @brief Provides an implementation of listings.h
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

#include "io/listings.h"
#include "adt/map.h"
#include "adt/map_elem.h"
#include "adt/list.h"
#include "adt/set.h"
#include "domain/athlete.h"
#include "domain/top_n_stats.h"

list_t *sort_list(list_t *athletes);

void paginate(list_t *athletes) {
    int page = 0;
    int size = 0;
    int command;
    list_size(athletes, &size);
    list_t *sorted_list = sort_list(athletes);

    printf("%d ATHLETES FOUND \n", size);

    if (size != 0) {
        bool whileOn = true;
        athlete_t athlete;

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
                    list_get(sorted_list, i, &athlete);
                    list_elem_print(athlete);
                }
                
            }
            printf("\nSHOWALL PAGINATED\n");
            if (LISTINGS_PAGE_SIZE < size - LISTINGS_PAGE_SIZE) 
                printf("1. Next %d\n", LISTINGS_PAGE_SIZE);
            printf("2. Return\n");
            
            read_integer(&command);

            if (command == 2)
                whileOn =false;
            else if (command == 1 && (LISTINGS_PAGE_SIZE < size - LISTINGS_PAGE_SIZE))
                page += LISTINGS_PAGE_SIZE;
            else
                printf("\nInvalid command.\n");
        }
    
    }

    free(sorted_list);
}

void paginate_set(set_t *statistics){

    int size;
    set_size(statistics, &size);
    printf("%d DISCIPLINES FOUND\n\n", size);

    printf("%30s", "DISCIPLINE");
	printf("%35s", "TOP MEDALS COUNTRY");
    printf("%15s", "PARTICIPATIONS");
    printf("===========================================================================================================================\n");

    set_print(statistics);
}

void print_host_details(char **host_data) {
    if (host_data == NULL) return;

    printf("\nHosting city: %s\n", host_data[0]);
    printf("Year: %s\n", host_data[1]);
    printf("Hosting country: %s\n", host_data[2]);
    printf("Duration of the event (days): %s\n\n", host_data[3]);
}

void print_athlete_info(char** medals_statistics, int medals_stats_size, char *country, char *athlete_id, int participations, int birth_year) {
    printf("\n=============== ATHLETE INFO ================\n");
    printf("AthleteID: %s\n", athlete_id);
    printf("Birth Year: %d\n", birth_year);
    printf("Country: %s\n", country);
    printf("Number of Participations: %d\n\n", participations);
    printf("=================== MEDALS ===================\n");

    for (int i = 0; i<medals_stats_size; i++) {
        printf("%s\n", medals_statistics[i]);
    }
}

void print_top_n(top_n_stats_t *top_n_list, int top_n_size, int n) {
        printf("\n\n%-40s | %-12s | %-30s | %-28s\n", "Country", "Total medals", "Average medals by game edition", "Average medals by game day");
        printf("--------------------------------------------------------------------------------------------------------------------------\n");

        top_n_stats_t *sorted_top_n = sort_top_n(top_n_list, top_n_size);

        if (n>top_n_size) {
            for (int i = 0; i<top_n_size; i++) {
             printf("%-40s | %-12d | %-30.2f | %-28.2f\n", sorted_top_n[i].country, sorted_top_n[i].total_medals, sorted_top_n[i].avg_medals_edition, sorted_top_n[i].avg_medals_game_days);
            }

        } else {
            for (int i = 0; i<n; i++) {
             printf("%-40s | %-12d | %-30.2f | %-28.2f\n", sorted_top_n[i].country, sorted_top_n[i].total_medals, sorted_top_n[i].avg_medals_edition, sorted_top_n[i].avg_medals_game_days);
            }
            printf("\n\nCould not find more than %d results.\n", top_n_size);
        }
}

top_n_stats_t *sort_top_n(top_n_stats_t *top_n_list, int top_n_size){
    top_n_stats_t *sorted_array = top_n_list;

    for (int i = 0; i<top_n_size; i++) {
        for (int j = 0; j<top_n_size; j++) {
            if (sorted_array[j].total_medals < sorted_array[j+1].total_medals) {
                top_n_stats_t temp;
                temp = sorted_array[j];
                sorted_array[j] = sorted_array[j+1];
                sorted_array[j+1] = temp; 
            } else if (sorted_array[j].total_medals == sorted_array[j+1].total_medals) {
                if (strcmp(sorted_array[j].country, sorted_array[j+1].country) > 0) {
                    top_n_stats_t temp;
                    temp = sorted_array[j];
                    sorted_array[j] = sorted_array[j+1];
                    sorted_array[j+1] = temp;
                }

            }
        }
    }

    return sorted_array;
}

list_t *sort_list(list_t *athletes) {
    int list_size_var;
    list_size(athletes, &list_size_var);
    list_t *sorted_list = athletes;

    for (int i = 0; i < list_size_var-1; i++) {
        for (int j = 0; j < list_size_var-i-1; j++) { 

            athlete_t elem, elem2;
            list_get(sorted_list, j, &elem);
            list_get(sorted_list, j+1, &elem2);

            if (strcmp(elem.athlete_name, elem2.athlete_name) > 0) {
                list_set(sorted_list, j+1, elem, &elem2);
                list_set(sorted_list, j, elem2, &elem);
            }
        }
    }
    
   return sorted_list;
}


 