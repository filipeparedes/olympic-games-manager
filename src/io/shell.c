/**
 * @file shell.c
 * 
 * @brief Provides an implementation of shell.h command interface loop
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 1.1.0
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
#include "io/shell.h"

static void show_welcome();

void run_shell(app_state_t *app) {
    //input
    char line[200];
    char *argv[MAX_ARGS];
    int argc;

    //output
    char msg[MAX_MSG_LEN];
    int status = CMD_OK;

    show_welcome();

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

 static void show_welcome() {
    printf("====================================================\n");
    printf("  ___  _                       _        ____ __  __ \n");
    printf(" / _ \\| |                     (_)      / ___|  \\/  |\n");
    printf("| | | | |_   _ _ __ ___  _ __  _  ___ | |  _| \\  / |\n");
    printf("| |_| | | |_| | | | | | | |_) | | (__ | |___| |  | |\n");
    printf(" \\___/|_|\\__, |_| |_| |_| .__/|_|\\___| \\____|_|  |_|\n");
    printf("          __/ |         | |                         \n");
    printf("         |___/          |_|                         \n");
    printf("\n");
    printf(" __          __  _                                 \n");
    printf(" \\ \\        / / | |                                \n");
    printf("  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___        \n");
    printf("   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\       \n");
    printf("    \\  /\\  /  __/ | (_| (_) | | | | | |  __/       \n");
    printf("     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|       \n");
    printf("\n");
    printf("====================================================\n");
    printf("      Welcome to the Olympic Games Manager v2.0     \n");
    printf("      Type 'help' to show all available commands.     \n");
    printf("====================================================\n\n");
}