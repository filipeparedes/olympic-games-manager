/**
 * @file shell.c
 * 
 * @brief Provides an implementation of shell.h command interface loop
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 1.0.0
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2026
 * 
 * @bug No known bugs.
 */
#include <stdio.h>
#include <string.h>
#include "core/app.h"
#include "core/command.h"
#include "io/input.h"
#include "shell.h"

 void run_shell(app_state_t *app) {
    //input
    char line[200];
    char *argv[MAX_ARGS];
    int argc;

    //output
    char msg[MAX_MSG_LEN];
    int status = CMD_OK;

    while (status != CMD_QUIT) {
        printf("\nbash@OlympicGM:~$ ");
        read_string(line, 200);

        if (strlen(line) == 0) continue;

        //Tokenization (turn str into array)
        argc = 0;
        char *token = strtok(line, " "); //divide on space

        while (token != NULL && argc < MAX_ARGS) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }

        if (argc <= 0) continue;

        status = command_dispatch(app, argc, argv, msg);
        if (status >= CMD_ERROR) 
            printf("[ERROR] %s\n", msg);
    }
 }