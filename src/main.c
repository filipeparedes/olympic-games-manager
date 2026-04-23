/**
 * @file main.c
 *
 * @brief Main file of the program. Contains its entry point.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "core/app.h"
#include "io/shell.h"

//Error codes
#define ARRAY_NO_MEMORY 1

int main() {
    app_state_t *app = create_app_state();
    if (app == NULL) return 1;

    run_shell(app);

    destroy_app_state(&app);

    return EXIT_SUCCESS;
}