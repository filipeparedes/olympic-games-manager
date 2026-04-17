/**
 * @file listElem.c
 * @brief Implements operations for ListElem.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "listElem.h"
#include <stdio.h>

void listElemPrint(ListElem elem) {
	printf("%40s", elem.athleteID);
	printf("%60s", elem.athleteName);
	printf("%15d", elem.gamesParticipations);
	printf("%30s", elem.firstGame);
	printf("%12d\n", elem.athleteBirth);
}