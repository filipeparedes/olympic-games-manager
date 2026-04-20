/**
 * @file app.h
 * 
 * @brief Header file containing the definition and related functions for the app state
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.1
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#include "adt/map.h"
#include "adt/set.h"
#include "adt/list.h"
#include "domain/host.h"
#include "domain/medal.h"
#include "domain/top_n_stats.h"

typedef struct app_state {
    list_t *athletes_list;
    map_t *hosts_map;
    medal_t *medals_array;

    //Metadata
    int medals_count;

    //System state
    bool data_loaded;
} app_state_t;

/**
 * @brief Initializes and allocates memory for an app_state_t
 * 
 * @return The pointer to the app state
 */
app_state_t *create_app_state();

/**
 * @brief Completely deletes an app_state_t from memory
 * 
 * @param app an address of the pointer to the app_state_t to delete
 */
void destroy_app_state(app_state_t **app);