/**
 * @file date.h
 * 
 * @brief Manages and represents date. 
 * Header file containing type definition for Date and related functions.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "io/input.h"

#define DATE_OK 0
#define DATE_NULL 1
#define STRING_NULL 2
#define STRING_INVALID 3

/**
 * @brief Structure representing a date.
 */
typedef struct date
{
    int year;    
    int month;   
    int day;   
    int hour;    
    int minute;  
    int second;  
} date_t;

/**
 * @brief Converts a string to a Date structure.
 *
 * This function parses a string representing a date and time,
 * and converts it to a Date structure.
 *
 * @param str The string representing the date in the format "YYYY-MM-DD HH:MM:SS".
 * @param date A pointer to the date that you want to change
 * 
 * @returns DATE_OK if the operation is sucessfull
 * @returns DATE_NULL if the date is null
 * @returns STRING_NULL if the string is null
 * @returns STRING_INVALID if the string is not in the correct format
 */
int string_to_date(char *str, date_t *date);