/**
 * @file list_elem.h
 * @brief Defines the type list_elem_t.
 * 
 * The list_elem_t is an alias to the type of elements 
 * held by an instance of the ADT List (list_t).
 * 
 * This alias must be changed according to the use-case.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com) - Original Version
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#include "domain/athlete.h"

/** Type definition. Change according to the use-case. */
typedef athlete_t list_elem_t;

/**
 * @brief Prints an element.
 * 
 * Must be implemented according to the concrete
 * type of list_elem_t.
 * 
 * @param elem [in] element to print
 */
void list_elem_print(list_elem_t elem);

