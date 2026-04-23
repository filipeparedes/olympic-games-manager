/**
 * @file top_n_stats.c
 * 
 * @brief Source file containing the implementation of functions.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.1.0
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "domain/top_n_stats.h"

static int compare_top_n(const void *a, const void *b);

void sort_top_n(top_n_stats_t *top_n_list, int top_n_size) {
    if (top_n_list == NULL || top_n_size <= 1) return;

    qsort(top_n_list, top_n_size, sizeof(top_n_stats_t), compare_top_n);
}

/**
 * @brief Comparison internal function for qsort.
 * Sorts by total medals (descending) and country name (ascending) as tie-breaker.
 */
static int compare_top_n(const void *a, const void *b) {
    const top_n_stats_t *stats_a = (const top_n_stats_t *)a;
    const top_n_stats_t *stats_b = (const top_n_stats_t *)b;

    /* 1. Primary criterion: Total medals (descending) */
    if (stats_b->total_medals != stats_a->total_medals) {
        return stats_b->total_medals - stats_a->total_medals;
    }

    /* 2. Secondary criterion: Country name (ascending) */
    return strcmp(stats_a->country, stats_b->country);
}