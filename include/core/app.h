/**
 * @file app.h
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @brief Header file containing the definition and related functions for the App State 
 */

#pragma once

#include "adt/map.h"
#include "adt/set.h"
#include "adt/list.h"
#include "domain/host.h"
#include "domain/medal.h"
#include "domain/topnstats.h"

typedef struct appState {
    PtList athletesList;
    PtMap hostsMap;
    PtMedal medalsArray;

    //Metadata
    int athletesCount;
    int hostsCount;
    int medalsCount;

    //System state
    bool dataLoaded;
} AppState;

typedef struct appState* PtAppState;

/**
 * @brief Initializes and allocates memory for an AppState
 * 
 * @return The pointer to the app state
 */
PtAppState createAppState();

/**
 * @brief Completely deletes an App State from memory
 * 
 * @param app a pointer to the app state to delete
 */
void destroyAppState (PtAppState* app);