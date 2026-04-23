/**
 * @file athlete.h
 * 
 * @brief Manages and represents athletes. 
 * Header file containing type definition for Athlete and related functions.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#define MAX_ID_LENGTH 50
#define MAX_NAME_LENGTH 100
#define MAX_GAME_LENGTH 50

typedef struct athlete {
    
    char athlete_id[MAX_ID_LENGTH]; 
    char athlete_name[MAX_NAME_LENGTH]; 
    int games_participations; // Num of Participations
    char first_game[MAX_GAME_LENGTH]; // First game of the athlete
    int athlete_birth;// year of birth

} athlete_t;

