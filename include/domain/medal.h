/**
 * @file medal.h
 * 
 * @brief Manages and represents medals. 
 * Header file containing type definition for Medal and related functions.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#define MAX_DISC_LENGTH 50
#define MAX_GAME_LENGTH 50
#define MAX_EVENT_LENGTH 100
#define MAX_ID_A_LENGTH 50
#define MAX_COUNTRY_LENGTH 50

/**
 * @brief Structure representing a medal.
 */
typedef struct medal {

    char discipline[MAX_DISC_LENGTH]; // Modalidade
    char game[MAX_GAME_LENGTH]; // Nome da edição dos jogos olímpicos ( ex beijing-2022)
    char event_title[MAX_EVENT_LENGTH]; // Titulo da prova ( ex Women's Ski cross)
    char gender; // M - Men, W- Women, X – Mixed, O - Open
    char medal_type; // G - GOLD, S - SILVER, B - BRONZE
    char participant_type; // A - Athlete, G - GameTeam
    char athlete_id [MAX_ID_A_LENGTH]; // Identificador de cada atleta
    char country[MAX_COUNTRY_LENGTH]; // País pelo qual o atleta competiu
    char country_code[4]; // Código do país

} medal_t;