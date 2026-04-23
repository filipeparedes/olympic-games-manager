/**
 * @file command.c
 *
 * @brief Implementation for the command.h dispatcher and internal commands.
 * The commands are implemented as static, as they should not be visible outside of this file.
 *
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 *
 * @version 1.0.2
 * @date 2026-04-20
 *
 * @copyright Copyright (c) 2026
 *
 * @bug No known bugs.
 */

#include "core/command.h"
#include "domain/athlete.h"
#include "domain/host.h"
#include "domain/medal.h"
#include "domain/top_n_stats.h"
#include "io/load.h"
#include "core/logic.h"
#include "core/app.h"
#include "io/listings.h"


#include <stdio.h>
#include <string.h>
#include <strings.h> // For Linux and macOS

/* --- Forward declaration of internal command funcs --- */
static int do_help(app_state_t *app, int argc, char **argv, char *msg);
static int do_quit(app_state_t *app, int argc, char **argv, char *msg);
static int do_load_a(app_state_t *app, int argc, char **argv, char *msg);
static int do_load_m(app_state_t *app, int argc, char **argv, char *msg);
static int do_load_h(app_state_t *app, int argc, char **argv, char *msg);
static int do_clear(app_state_t *app, int argc, char **argv, char *msg);
static int do_show_all(app_state_t *app, int argc, char **argv, char *msg);
static int do_show_participations(app_state_t *app, int argc, char **argv, char *msg);
static int do_show_first(app_state_t *app, int argc, char **argv, char *msg);
static int do_show_host(app_state_t *app, int argc, char **argv, char *msg);
static int do_discipline_statistics(app_state_t *app, int argc, char **argv, char *msg);
static int do_athlete_info(app_state_t *app, int argc, char **argv, char *msg);
static int do_topn(app_state_t *app, int argc, char **argv, char *msg);
static int do_medals_won(app_state_t *app, int argc, char **argv, char *msg);

/* --- Command Table --- */
// Associates user's input with functions and descriptions
static command_t commands[] = {
    {"help",                  do_help,                  "Displays this help menu or help for a specific command"},
    {"quit",                  do_quit,                  "Terminates the application"},
    {"load_a",                do_load_a,                "Loads athlete records from file"},
    {"load_m",                do_load_m,                "Loads medal records from file"},
    {"load_h",                do_load_h,                "Loads host records from file"},
    {"clear",                 do_clear,                 "Clears all loaded records from memory"},
    {"show_all",              do_show_all,              "Lists all loaded athletes with pagination"},
    {"show_participations",   do_show_participations,   "Lists athletes with at least N participations. Usage: show_participations <n>"},
    {"show_first",            do_show_first,            "Lists athletes whose first participation was in a given year. Usage: show_first <YYYY>"},
    {"show_host",             do_show_host,             "Shows details for a given Olympic edition. Usage: show_host <City YYYY>"},
    {"discipline_statistics", do_discipline_statistics, "Shows discipline statistics for a given edition. Usage: discipline_statistics <City YYYY>"},
    {"athlete_info",          do_athlete_info,          "Shows full info and medal breakdown for an athlete. Usage: athlete_info <athleteID>"},
    {"topn",                  do_topn,                  "Shows top N countries by medals in a season/period. Usage: topn <season> <startYear> <endYear> <n>"},
    {"medals_won",            do_medals_won,            "Shows medals won by a country in a season from a given year. Usage: medals_won <country> <year> <season>"},
    {NULL, NULL, NULL}
};

/* ------------------------------------------------------------------ */
/*  Dispatcher                                                          */
/* ------------------------------------------------------------------ */

int command_dispatch(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc <= 0) return CMD_OK;

    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcasecmp(argv[0], commands[i].name) == 0) {
            return commands[i].func(app, argc, argv, msg);
        }
    }

    snprintf(msg, MAX_MSG_LEN, "Unknown command: '%s'. Type 'help' for a list of commands.", argv[0]);
    return CMD_ERROR;
}

/* ------------------------------------------------------------------ */
/*  Internal Command Implementations                                    */
/* ------------------------------------------------------------------ */

/**
 * @brief Displays the help menu or detailed help for a specific command.
 *
 * Usage: help [command]
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK
 */
static int do_help(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc > 2) {
        snprintf(msg, MAX_MSG_LEN, "Usage: help [command]");
        return CMD_ERROR;
    }

    // help <command> — show description for that specific command
    if (argc == 2) {
        for (int i = 0; commands[i].name != NULL; i++) {
            if (strcasecmp(argv[1], commands[i].name) == 0) {
                printf("  %-25s %s\n", commands[i].name, commands[i].description);
                return CMD_OK;
            }
        }
        snprintf(msg, MAX_MSG_LEN, "No such command: '%s'", argv[1]);
        return CMD_ERROR;
    }

    // help — full list
    printf("\nAvailable commands:\n\n");
    for (int i = 0; commands[i].name != NULL; i++) {
        printf("  %-25s %s\n", commands[i].name, commands[i].description);
    }
    printf("\n");

    return CMD_OK;
}

/**
 * @brief Terminates the application.
 *
 * Usage: quit
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_QUIT to signal the shell to stop the loop
 */
static int do_quit(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc > 1) {
        snprintf(msg, MAX_MSG_LEN, "Usage: quit (no arguments expected)");
        return CMD_ERROR;
    }

    msg[0] = '\0';
    printf("Exiting OlympicGM... See you soon!\n");

    return CMD_QUIT;
}

/**
 * @brief Loads athlete records from file into the app state.
 *
 * Usage: load_a
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on failure
 */
static int do_load_a(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc > 1) {
        snprintf(msg, MAX_MSG_LEN, "Usage: load_a (no arguments expected)");
        return CMD_ERROR;
    }

    int athletes_size = 0;
    int ret = import_athletes(app->athletes_list, &athletes_size);

    switch (ret) {
        case LOAD_OK:
            printf("%d athlete records imported.\n", athletes_size);
            app->athletes_loaded = true;
            return CMD_OK;
        case FILE_NOT_FOUND:
            snprintf(msg, MAX_MSG_LEN, "load_a: athletes file not found.");
            return CMD_ERROR;
        default:
            snprintf(msg, MAX_MSG_LEN, "load_a: unexpected error (code %d).", ret);
            return CMD_ERROR;
    }
}

/**
 * @brief Loads medal records from file into the app state.
 *
 * Usage: load_m
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on failure
 */
static int do_load_m(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc > 1) {
        snprintf(msg, MAX_MSG_LEN, "Usage: load_m (no arguments expected)");
        return CMD_ERROR;
    }
 
    // Pre-allocate the array — import_medals requires a non-NULL pointer
    FILE *f = fopen("data/medals.csv", "r");
    if (f == NULL) {
        snprintf(msg, MAX_MSG_LEN, "load_m: medals file not found.");
        return CMD_ERROR;
    }
    int line_count = count_file_lines(f);
    fclose(f);
 
    if (app->medals_array != NULL) free(app->medals_array);
    app->medals_array = (medal_t *)malloc(sizeof(medal_t) * line_count);
    if (app->medals_array == NULL) {
        snprintf(msg, MAX_MSG_LEN, "load_m: insufficient memory.");
        return CMD_ERROR;
    }
 
    int ret = import_medals(app->medals_array, &app->medals_count);
 
    switch (ret) {
        case LOAD_OK:
            printf("%d medal records imported.\n", app->medals_count);
            app->medals_loaded = true;
            return CMD_OK;
        case FILE_NOT_FOUND:
            snprintf(msg, MAX_MSG_LEN, "load_m: medals file not found.");
            return CMD_ERROR;
        default:
            snprintf(msg, MAX_MSG_LEN, "load_m: unexpected error (code %d).", ret);
            return CMD_ERROR;
    }
}

/**
 * @brief Loads host records from file into the app state.
 *
 * Usage: load_h
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on failure
 */
static int do_load_h(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc > 1) {
        snprintf(msg, MAX_MSG_LEN, "Usage: load_h (no arguments expected)");
        return CMD_ERROR;
    }

    int hosts_size = 0;
    int ret = import_hosts(app->hosts_map, &hosts_size);

    switch (ret) {
        case LOAD_OK:
            printf("%d host records imported.\n", hosts_size);
            app->hosts_loaded = true;
            return CMD_OK;
        case FILE_NOT_FOUND:
            snprintf(msg, MAX_MSG_LEN, "load_h: hosts file not found.");
            return CMD_ERROR;
        default:
            snprintf(msg, MAX_MSG_LEN, "load_h: unexpected error (code %d).", ret);
            return CMD_ERROR;
    }
}

/**
 * @brief Clears all loaded records from memory and resets counters.
 *
 * Usage: clear
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK
 */
static int do_clear(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc > 1) {
        snprintf(msg, MAX_MSG_LEN, "Usage: clear (no arguments expected)");
        return CMD_ERROR;
    }

    // Snapshot sizes before clearing for the confirmation message
    int prev_athletes = 0, prev_hosts = 0;
    list_size(app->athletes_list, &prev_athletes);
    map_size(app->hosts_map, &prev_hosts);
    int prev_medals = app->medals_count;

    if (app->hosts_map != NULL) {
        map_destroy(&app->hosts_map);
        app->hosts_map = NULL;
    }
    if (app->athletes_list != NULL) {
        list_destroy(&app->athletes_list);
        app->athletes_list = NULL;
    }
    if (app->medals_array != NULL) {
        free(app->medals_array);
        app->medals_array = NULL;
    }

    //recreate list & map after destroying
    app->athletes_list = list_create();
    app->hosts_map = map_create();

    app->medals_count = 0;
    app->athletes_loaded = false;
    app->medals_loaded   = false;
    app->hosts_loaded    = false;

    printf("Records deleted from Athletes (%d) | Medals (%d) | Hosts (%d)\n",
           prev_athletes, prev_medals, prev_hosts);

    return CMD_OK;
}

/**
 * @brief Lists all loaded athletes with pagination.
 *
 * Usage: show_all
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR if no data is loaded
 */
static int do_show_all(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc > 1) {
        snprintf(msg, MAX_MSG_LEN, "Usage: show_all (no arguments expected)");
        return CMD_ERROR;
    }
    if (!app->athletes_loaded) {
        snprintf(msg, MAX_MSG_LEN, "show_all: no athlete records loaded. Run 'load_a' first.");
        return CMD_ERROR;
    }

    paginate(app->athletes_list);
    return CMD_OK;
}

/**
 * @brief Lists athletes with at least N participations.
 *
 * Usage: show_participations <n>
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments — argv[1] is the minimum participation count
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on bad input or no data
 */
static int do_show_participations(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc != 2) {
        snprintf(msg, MAX_MSG_LEN, "Usage: show_participations <n>");
        return CMD_ERROR;
    }
    if (!app->athletes_loaded) {
        snprintf(msg, MAX_MSG_LEN, "show_participations: no athlete records loaded. Run 'load_a' first.");
        return CMD_ERROR;
    }

    int participations;
    if (sscanf(argv[1], "%d", &participations) != 1 || participations < 1) {
        snprintf(msg, MAX_MSG_LEN, "show_participations: invalid argument '%s'. Expected a positive integer.", argv[1]);
        return CMD_ERROR;
    }

    list_t *filtered_list = filter_list_by_participations(app->athletes_list, participations);
    int filtered_size;
    list_size(filtered_list, &filtered_size);

    if (filtered_size == 0) {
        printf("No athletes found with at least %d participation(s).\n", participations);
    } else {
        paginate(filtered_list);
    }

    list_destroy(&filtered_list);
    return CMD_OK;
}

/**
 * @brief Lists athletes whose first participation was in a given year.
 *
 * Usage: show_first <YYYY>
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments — argv[1] is the year (YYYY)
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on bad input or no data
 */
static int do_show_first(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc != 2) {
        snprintf(msg, MAX_MSG_LEN, "Usage: show_first <YYYY>");
        return CMD_ERROR;
    }
    if (!app->athletes_loaded) {
        snprintf(msg, MAX_MSG_LEN, "show_first: no athlete records loaded. Run 'load_a' first.");
        return CMD_ERROR;
    }

    // Validate that the argument looks like a 4-digit year
    int year;
    if (sscanf(argv[1], "%d", &year) != 1 || year < 1000 || year > 9999) {
        snprintf(msg, MAX_MSG_LEN, "show_first: invalid year '%s'. Expected format: YYYY.", argv[1]);
        return CMD_ERROR;
    }

    list_t *filtered_list = filter_list_by_first_year(app->athletes_list, argv[1]);
    int filtered_size;
    list_size(filtered_list, &filtered_size);

    if (filtered_size == 0) {
        printf("No athletes whose first participation was in %s.\n", argv[1]);
    } else {
        paginate(filtered_list);
    }

    list_destroy(&filtered_list);
    return CMD_OK;
}

/**
 * @brief Shows details for a given Olympic edition (host).
 *
 * Usage: show_host <City YYYY>
 * Example: show_host Montreal 1976
 *
 * Since the edition name is two tokens ("Montreal 1976"), argv[1] and argv[2]
 * are joined back into a single string before the lookup.
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments — argv[1] city, argv[2] year
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on bad input or no data
 */
static int do_show_host(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc != 3) {
        snprintf(msg, MAX_MSG_LEN, "Usage: show_host <City YYYY>  (e.g. show_host Montreal 1976)");
        return CMD_ERROR;
    }
    if (!app->hosts_loaded) {
        snprintf(msg, MAX_MSG_LEN, "show_host: no host records loaded. Run 'load_h' first.");
        return CMD_ERROR;
    }

    char edition[50];
    snprintf(edition, sizeof(edition), "%s %s", argv[1], argv[2]);

    char **host_data = get_host_data(app->hosts_map, edition);

    if (host_data == NULL) {
        snprintf(msg, MAX_MSG_LEN, "show_host: edition '%s' not found.", edition);
        return CMD_ERROR;
    }

    print_host_details(host_data);
    free(host_data);

    return CMD_OK;
}

/**
 * @brief Shows discipline statistics for a given Olympic edition.
 *
 * Usage: discipline_statistics <City YYYY>
 * Example: discipline_statistics Sydney 2000
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments — argv[1] city, argv[2] year
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on bad input or no data
 */
static int do_discipline_statistics(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc != 3) {
        snprintf(msg, MAX_MSG_LEN, "Usage: discipline_statistics <City YYYY>  (e.g. discipline_statistics Sydney 2000)");
        return CMD_ERROR;
    }
    if (!app->medals_loaded || !app->hosts_loaded) {
        snprintf(msg, MAX_MSG_LEN, "discipline_statistics: medals and hosts must be loaded first (load_m, load_h).");
        return CMD_ERROR;
    }

    char edition[50];
    snprintf(edition, sizeof(edition), "%s %s", argv[1], argv[2]);

    set_t *set = get_discipline_statistics(app->medals_array, app->medals_count, app->hosts_map, edition);

    int size;
    set_size(set, &size);

    if (size == 0) {
        printf("No discipline statistics found for '%s'.\n", edition);
    } else {
        paginate_set(set);
    }

    set_destroy(&set);
    return CMD_OK;
}

/**
 * @brief Shows full info and medal breakdown for a given athlete.
 *
 * Usage: athlete_info <athleteID>
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments — argv[1] is the athlete ID
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on bad input or no data
 */
static int do_athlete_info(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc != 2) {
        snprintf(msg, MAX_MSG_LEN, "Usage: athlete_info <athleteID>");
        return CMD_ERROR;
    }
    if (!app->athletes_loaded) {
        snprintf(msg, MAX_MSG_LEN, "athlete_info: athletes and medals must be loaded first (load_a, load_m).");
        return CMD_ERROR;
    }

    int participations, birth_year, medals_stats_size;
    char country[30];

    char **medals_statistics = get_athlete_info(
        app->medals_array, app->medals_count,
        app->athletes_list, app->hosts_map,
        argv[1], country, &participations, &birth_year, &medals_stats_size
    );

    if (medals_statistics == NULL) {
        snprintf(msg, MAX_MSG_LEN, "athlete_info: athlete '%s' not found.", argv[1]);
        return CMD_ERROR;
    }

    print_athlete_info(medals_statistics, medals_stats_size, country, argv[1], participations, birth_year);
    return CMD_OK;
}

/**
 * @brief Shows the top N countries by medals won in a given season and year range.
 *
 * Usage: topn <season> <startYear> <endYear> <n>
 * Example: topn Summer 1990 2010 5
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments: argv[1] season, argv[2] startYear, argv[3] endYear, argv[4] n
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on bad input or no data
 */
static int do_topn(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc != 5) {
        snprintf(msg, MAX_MSG_LEN, "Usage: topn <season> <startYear> <endYear> <n>  (e.g. topn Summer 1990 2010 5)");
        return CMD_ERROR;
    }
    if (!app->medals_loaded) {
        snprintf(msg, MAX_MSG_LEN, "topn: medals must be loaded first (load_m).");
        return CMD_ERROR;
    }

    int start_year, end_year, n;
    if (sscanf(argv[2], "%d", &start_year) != 1 ||
        sscanf(argv[3], "%d", &end_year)   != 1 ||
        sscanf(argv[4], "%d", &n)          != 1 || n < 1) {
        snprintf(msg, MAX_MSG_LEN, "topn: invalid arguments. Years must be integers and n must be >= 1.");
        return CMD_ERROR;
    }
    if (start_year > end_year) {
        snprintf(msg, MAX_MSG_LEN, "topn: startYear (%d) must not be greater than endYear (%d).", start_year, end_year);
        return CMD_ERROR;
    }

    int top_n_size;
    top_n_stats_t *top_n_list = get_top_n_countries(
        app->medals_array, app->medals_count,
        app->hosts_map, app->athletes_list,
        argv[1], start_year, end_year, &top_n_size
    );

    if (top_n_list == NULL) {
        snprintf(msg, MAX_MSG_LEN, "topn: no results found.");
        return CMD_ERROR;
    }

    print_top_n(top_n_list, n, top_n_size);
    return CMD_OK;
}

/**
 * @brief Shows medals won by a country from a given year in a given season.
 *
 * Usage: medals_won <country> <year> <season>
 * Example: medals_won Portugal 2000 Summer
 *
 * @param app  Pointer to the program app state
 * @param argc Number of arguments
 * @param argv Array of arguments: argv[1] country, argv[2] year, argv[3] season
 * @param msg  [out] Message buffer for errors/feedback
 * @return CMD_OK on success, CMD_ERROR on bad input or no data
 */
static int do_medals_won(app_state_t *app, int argc, char **argv, char *msg) {
    if (argc != 4) {
        snprintf(msg, MAX_MSG_LEN, "Usage: medals_won <country> <year> <season>  (e.g. medals_won Portugal 2000 Summer)");
        return CMD_ERROR;
    }
    if (!app->medals_loaded) {
        snprintf(msg, MAX_MSG_LEN, "medals_won: medals must be loaded first (load_m).");
        return CMD_ERROR;
    }

    int year;
    if (sscanf(argv[2], "%d", &year) != 1 || year < 1000 || year > 9999) {
        snprintf(msg, MAX_MSG_LEN, "medals_won: invalid year '%s'. Expected format: YYYY.", argv[2]);
        return CMD_ERROR;
    }

    get_medals_won(app->medals_array, app->medals_count, app->hosts_map, argv[1], year, argv[3]);
    return CMD_OK;
}