/**
 * @file athlete.h
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * @brief Manages and represents athletes. 
 * Header file containing type definition for Athlete and related functions.
 */

#pragma once

#define MAX_ID_LENGTH 50
#define MAX_NAME_LENGTH 100
#define MAX_GAME_LENGTH 50

typedef struct athlete {
    
    char athleteID[MAX_ID_LENGTH]; 
    char athleteName[MAX_NAME_LENGTH]; 
    int gamesParticipations; // Num of Participations
    char firstGame[MAX_GAME_LENGTH]; // First game of the athlete
    int athleteBirth;// year of birth

} Athlete;

