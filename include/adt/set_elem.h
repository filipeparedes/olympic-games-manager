/**
 * @file set_elem.h
 * @brief Defines the type set_elem_t.
 * 
 * The set_elem_t is an alias to the type of elements 
 * held by an instance of the ADT Set (set_t).
 * 
 * This alias must be changed according to the use-case.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.1
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#include <string.h>
#include "domain/discipline_stats.h"

/** Type definition. Change according to the use-case. */
typedef discipline_stats_t set_elem_t;

/**
 * @brief Prints an element.
 * 
 * Must be implemented according to the concrete
 * type of set_elem_t.
 * 
 * @param elem [in] element to print
 */
void set_elem_print(set_elem_t elem);