/**
 * @file command.h
 * 
 * @brief Header file containing the signatures for all command functions.
 * All commands receive the app state and return an integer (error code code).
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 1.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once
#include "app.h" 

//Status codes
#define CMD_OK 0
#define CMD_QUIT 1
#define CMD_ERROR 2

#define MAX_MSG_LEN 256

/**
 * @brief represents a single command
 * 
 * @param app program's app state
 * @param argc number of arguments
 * @param argv string array with arguments
 * @param msg [out] buffer to write error message if something goes wrong
 */
typedef int (*command_func_t)(app_state_t *app, int argc, char **argv, char *msg);

typedef struct command {
    char *name;          //user input
    command_func_t func; //function to call
    char *description;   //for the 'help' command
} command_t;

/**
 * @brief Finds and executes a command based on its name
 * 
 * @param app - the program app state
 * @param argc - number of arguments
 * @param argv - string array with the arguments
 * @param msg [out] buffer to write error message from command if something goes wrong
 * 
 * @return An integer correspondent to a status code
 */
int command_dispatch(app_state_t *app, int argc, char **argv, char *msg);