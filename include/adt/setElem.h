/**
 * @file setElem.h
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * @brief Defines the type SetElem.
 * 
 * The SetElem is an alias to the type of elements 
 * held by an instance of the ADT Set (PtSet).
 * 
 * This alias must be changed according to the use-case.
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