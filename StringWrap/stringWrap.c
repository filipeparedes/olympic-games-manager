/**
 * @file stringWrap.c
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Header file for string wrapping operations.
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "stringWrap.h"
#include <string.h>

StringWrap stringWrapCreate(char *str) {
    StringWrap sw;
    strcpy(sw.text, str);
    return sw;
}