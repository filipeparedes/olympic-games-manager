/**
 * @file medal.h
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * @brief Manages and represents medals. Header file containing type definition for Medal and related functions.
 */

#pragma once

#define MAX_DISC_LENGTH 50
#define MAX_GAME_LENGTH 50
#define MAX_EVENT_LENGTH 100
#define MAX_ID_A_LENGTH 50
#define MAX_COUNTRY_LENGTH 50

typedef struct medal Medal;
typedef Medal* PtMedal;

typedef struct medal {

    char discipline[MAX_DISC_LENGTH]; // Modalidade
    char game[MAX_GAME_LENGTH]; // Nome da edição dos jogos olímpicos ( ex beijing-2022)
    char eventTitle[MAX_EVENT_LENGTH]; // Titulo da prova ( ex Women's Ski cross)
    char gender; // M - Men, W- Women, X – Mixed, O - Open
    char medalType; // G - GOLD, S - SILVER, B - BRONZE
    char participantType; // A - Athlete, G - GameTeam
    char athleteID [MAX_ID_A_LENGTH]; // Identificador de cada atleta
    char country[MAX_COUNTRY_LENGTH]; // País pelo qual o atleta competiu
    char countryCode[4]; // Código do país

} Medal;