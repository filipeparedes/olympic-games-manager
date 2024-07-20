/**
 * @file date.c
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Manages and represents dates. Source file containing the implementation of functions.
 * 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "date.h"
#include "../Input/input.h"

int stringToDate(char* str, Date* date){

    char seconds[3];

    if (str == NULL) return STRING_NULL;
    if (date == NULL) return DATE_NULL;

    char** split = splitString(str, 2, "T");
        if (split[0] == NULL || split[1] == NULL){
            free(split);
            return STRING_INVALID;
        } 
    char** splitDate = splitString(split[0], 3, "-");
        if (splitDate[0] == NULL || splitDate[1] == NULL || splitDate[3] == NULL){
            free(split);
            free(splitDate);
            return STRING_INVALID;
        } 
    char** splitTime = splitString(split[1], 3, ":");
        if (splitTime[0] == NULL || splitTime[1] == NULL || splitDate[3] == NULL){
            free(split);
            free(splitTime);
            free(splitDate);
            return STRING_INVALID;
        } 

    date->year = atoi(splitDate[0]);
    date->month = atoi(splitDate[1]);
    date->day = atoi(splitDate[2]);
    
    date->hour = atoi(splitTime[0]);
    date->minute = atoi(splitTime[1]);

    strncpy(seconds, splitTime[2], 2);
    date->second = atoi(seconds);

    free(split);
    free(splitTime);
    free(splitDate);

    return DATE_OK;
}
