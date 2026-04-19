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
    
    char athleteID[MAX_ID_LENGTH]; // Identificador único do atleta
    char athleteName[MAX_NAME_LENGTH]; // Nome do atleta
    int gamesParticipations; // Número de jogos em que participou
    char firstGame[MAX_GAME_LENGTH]; // O jogo em que participou pela primeira vez.
    int athleteBirth;// Ano de nascimento

} Athlete;

