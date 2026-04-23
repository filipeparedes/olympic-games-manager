/**
 * @file app.h
 *
 * @brief Contains implementation for app.h
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.2
 * @date 20-04-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "core/app.h"
#include "adt/map_elem.h"
#include "adt/map.h"
#include "adt/set.h"
#include "adt/set_elem.h"
#include "adt/list.h"
#include "adt/list_elem.h"
#include "domain/medal.h"
#include "domain/discipline_stats.h"
#include "domain/top_n_stats.h"

app_state_t *create_app_state() {
    app_state_t *app = (app_state_t*)malloc(sizeof(app_state_t));
    if (app == NULL) return NULL;

    //initialize structures
    app->athletes_list = list_create();
    app->hosts_map = map_create();
    app->medals_array = NULL; //allocated during load

    //initialize counters
    app->medals_count = 0;
    app->athletes_loaded = false;
    app->medals_loaded = false;
    app->hosts_loaded = false;

    return app;
}

void destroy_app_state(app_state_t **app) {
    if (app == NULL || *app == NULL) return;

    //free internal structures
    if ((*app)->athletes_list != NULL) list_destroy(&(*app)->athletes_list);
    if ((*app)->hosts_map != NULL) map_destroy(&(*app)->hosts_map);
    if ((*app)->medals_array != NULL) free((*app)->medals_array);

    free(*app);
    *app = NULL;
}