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
	printf("Disciplina: %s\n", elem.discipline);
	printf("Edição: %s\n", elem.game);
	printf("Título: %s\n", elem.eventTitle);
	printf("Género: %c\n", elem.gender);
	printf("Medalha: %c\n", elem.medalType);
	printf("Tipo de Participante: %c\n", elem.participantType);
	printf("ID Atleta: %s\n", elem.athleteID);
	printf("País: %s\n", elem.country);
	printf("Código País: %s\n", elem.countryCode);
}