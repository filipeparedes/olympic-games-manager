/**
 * @file setElem.c
 * 
 * @brief Implements operations for set_elem.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2026
 * 
 * @bug No known bugs.
 */

#include "adt/set_elem.h"
#include <stdio.h>
#include <string.h>


void set_elem_print(set_elem_t elem) {
    printf("%30s", elem.discipline_name);
	printf("%35s", elem.top_medals_country);
	printf("%15f", elem.women_ratio);
}