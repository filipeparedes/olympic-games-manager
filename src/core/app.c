/**
 * @file app.h
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * @brief Contains implementation for app.h
 * @version 1
 * @date 20-04-2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "core/app.h"
#include "adt/mapElem.h"
#include "adt/map.h"
#include "adt/set.h"
#include "adt/setElem.h"
#include "adt/list.h"
#include "adt/listElem.h"
#include "domain/medal.h"
#include "domain/disciplinestats.h"
#include "domain/topnstats.h"

PtAppState createAppState() {
    PtAppState app = (PtAppState)malloc(sizeof(AppState));
    if (app == NULL) return NULL;

    //initialize structures
    app->athletesList = listCreate();
    app->hostsMap = mapCreate();
    app->medalsArray = NULL; //allocated during load

    //initialize counters
    app->athletesCount = 0;
    app->hostsCount = 0;
    app->medalsCount = 0;
    app->dataLoaded = false;

    return app;
}

void deleteAppState(PtAppState* app) {
    if (app == NULL || *app == NULL) return;

    //free internal structures
    if ((*app)->athletesList != NULL) listDestroy(&(*app)->athletesList);
    if ((*app)->hostsMap != NULL) mapDestroy(&(*app)->hostsMap);
    if ((*app)->medalsArray != NULL) free((*app)->medalsArray);

    free(*app);
    *app = NULL;
}