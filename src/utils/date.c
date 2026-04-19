/**
 * @file date.c
 * @author Filipe Paredes (filipeparedes3@gmail.com)
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

#include "utils/date.h"
#include "io/input.h"

int stringToDate(char* str, Date* date){
    if (str == NULL) return STRING_NULL;
    if (date == NULL) return DATE_NULL;

    char** split = splitString(str, 2, "T");
    if (split == NULL || split[0] == NULL || split[1] == NULL){
        if(split) free(split);
        return STRING_INVALID;
    } 

    char** splitDate = splitString(split[0], 3, "-");
    if (splitDate == NULL || splitDate[0] == NULL || splitDate[1] == NULL || splitDate[2] == NULL){
        free(split);
        if (splitDate) free(splitDate);
        return STRING_INVALID;
    } 

    char** splitTime = splitString(split[1], 3, ":");
    if (splitTime == NULL || splitTime[0] == NULL || splitTime[1] == NULL || splitTime[2] == NULL){
        free(split);
        free(splitDate);
        if (splitTime) free(splitTime);
        return STRING_INVALID;
    } 

    date->year = atoi(splitDate[0]);
    date->month = atoi(splitDate[1]);
    date->day = atoi(splitDate[2]);
    
    date->hour = atoi(splitTime[0]);
    date->minute = atoi(splitTime[1]);
    date->second = atoi(splitTime[2]);  

    free(split);
    free(splitDate);
    free(splitTime);

    return DATE_OK;
}
