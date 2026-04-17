/**
 * @file setElem.c
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Implements operations for setElem.
 * @version 0.3
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "setElem.h"
#include <stdio.h>
#include <string.h>


void setElemPrint(SetElem elem) {
    printf("%30s", elem.disciplineName);
	printf("%35s", elem.topMedalsCountry);
	printf("%15f", elem.womenRatio);
}