/**
 * @file setElem.h
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Defines the type SetElem.
 * 
 * The SetElem is an alias to the type of elements 
 * held by an instance of the ADT Set (PtSet).
 * 
 * This alias must be changed according to the use-case.
 * 
 * @version 0.3
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string.h>
#include "domain/disciplinestats.h"

/** Type definition. Change according to the use-case. */
typedef DisciplineStats SetElem;

/**
 * @brief Prints an element.
 * 
 * Must be implemented according to the concrete
 * type of SetElem.
 * 
 * @param elem [in] element to print
 */
void setElemPrint(SetElem elem);