/**
 * @file main.c
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Main file of the program. Contains its entry point. Represents a command prompt.
 * 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h> 
#include <stdlib.h>


#include "./Input/input.h"
#include "./Host/host.h"
#include "./Medal/medal.h"
#include "./Athlete/athlete.h"
#include "./StringWrap/stringWrap.h"
#include "./ADTMap/map.h"
#include "./ADTList/list.h"

#define ARRAY_NO_MEMORY 1

#define MAX_COMMAND_LENGTH 20
#define MAX_LINE_LENGTH 1000

int main() {

    bool quit = false;
    char command[MAX_COMMAND_LENGTH];

    //TODO: get specific size of each file.

    PtList medalsList = listCreate();
    PtMap athletesMap = mapCreate();
    PtHost hostsArray = (Host*) malloc(sizeof(Host)* 1); 
    
    if (medalsList == NULL) return LIST_NO_MEMORY;
    if (athletesMap == NULL) return MAP_NO_MEMORY;
    if (hostsArray == NULL) return ARRAY_NO_MEMORY;

    do {
        printf("\nbash@projeto-atad:~$ ");
        readString(command, MAX_COMMAND_LENGTH);

        //Makes every character in the command lowercase
        for (int i = 0; command[i]; i++) {
            command[i] = tolower(command[i]);
        }

        if (strcmp(command, "load_a") == 0) {
            printf("Not implemented yet.");
        }   
        else if (strcmp(command, "load_m") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "load_h") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "clear") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "show_all") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "show_participations") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "show_first") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "show_host") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "discipline_statistics") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "athlete_info") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "topn") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "medals_won") == 0) {
            printf("Not implemented yet.");
        }
        else if (strcmp(command, "quit") == 0) {
            quit = true;
        }
        else {
            printf("Unknown Command");
        }
    } while (!quit);

    return EXIT_SUCCESS;
}
