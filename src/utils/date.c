/**
 * @file date.c
 * 
 * @brief Manages and represents dates. Source file containing the implementation of functions.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "utils/date.h"
#include "io/input.h"

int string_to_date(char *str, date_t *date){
    if (str == NULL) return STRING_NULL;
    if (date == NULL) return DATE_NULL;

    char **split = split_string(str, 2, "T");
    if (split == NULL || split[0] == NULL || split[1] == NULL){
        if(split) free(split);
        return STRING_INVALID;
    } 

    char **split_date = split_string(split[0], 3, "-");
    if (split_date == NULL || split_date[0] == NULL || split_date[1] == NULL || split_date[2] == NULL){
        free(split);
        if (split_date) free(split_date);
        return STRING_INVALID;
    } 

    char **split_time = split_string(split[1], 3, ":");
    if (split_time == NULL || split_time[0] == NULL || split_time[1] == NULL || split_time[2] == NULL){
        free(split);
        free(split_date);
        if (split_time) free(split_time);
        return STRING_INVALID;
    } 

    date->year = atoi(split_date[0]);
    date->month = atoi(split_date[1]);
    date->day = atoi(split_date[2]);
    
    date->hour = atoi(split_time[0]);
    date->minute = atoi(split_time[1]);
    date->second = atoi(split_time[2]);  

    free(split);
    free(split_date);
    free(split_time);

    return DATE_OK;
}
