/**
 * @file shell.h
 * 
 * @brief Header file for the command-line interface
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 1.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#include "core/app.h"

#define MAX_ARGS 10

/**
 * @brief Starts the interactive shell loop.
 * This function will keep the program running, reading input and dispatching commands
 * until the 'quit' commad is issued.
 * 
 * @param app Pointer to the program app state
 */
void run_shell(app_state_t *app);
