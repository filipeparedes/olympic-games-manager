/**
 * @file list_elem.c
 * @brief Implements operations for list_elem_t.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com) - Original Version 
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#include "adt/list_elem.h"
#include <stdio.h>

void listElemPrint(list_elem_t elem) {
	printf("%40s", elem.athlete_id);
	printf("%60s", elem.athlete_name);
	printf("%15d", elem.games_participations);
	printf("%30s", elem.first_game);
	printf("%12d\n", elem.athlete_birth);
}