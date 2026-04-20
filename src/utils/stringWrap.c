/**
 * @file string_wrap.c
 * 
 * @brief Header file for string wrapping operations.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 */
#include "utils/string_wrap.h"
#include <string.h>

string_wrap_t stringWrapCreate(char *str) {
    string_wrap_t sw;
    strcpy(sw.text, str);
    return sw;
}