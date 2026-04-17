/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "adt/mapElem.h"
#include <stdio.h>
#include <string.h>

void mapKeyPrint(MapKey key) {
	printf("ID: %s\n", key.text);
}

void mapValuePrint(MapValue value) {
	printf("%20d-%d-%d", value.gameEndDate.year, value.gameEndDate.month, value.gameEndDate.day);
	printf("%20d-%d-%d", value.gameStartDate.year, value.gameStartDate.month, value.gameStartDate.day);
	printf("%30s", value.location);
	printf("%30s", value.gameName);
	printf("%12s", value.season);
	printf("%12d\n", value.gameYear);
}

int mapKeyCompare(MapKey key1, MapKey key2) {
	return strcmp(key1.text, key2.text);
}