/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <stdio.h>
#include <string.h>

void mapKeyPrint(MapKey key) {
	printf("ID: %s\n", key.text);
}

void mapValuePrint(MapValue value) {
	printf("%40s", value.athleteID);
	printf("%60s", value.athleteName);
	printf("%15d", value.gamesParticipations);
	printf("%30s", value.firstGame);
	printf("%12d\n", value.athleteBirth);
}

int mapKeyCompare(MapKey key1, MapKey key2) {
	return strcmp(key1.text, key2.text);
}