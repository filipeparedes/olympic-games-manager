# OlympicGM — Technical Manual

**Author:** Filipe Paredes (filipeparedes3@gmail.com)

**Version:** 1.0.0

**Date:** 2026-04-21

---

## Table of Contents

1. [Project Overview](#1-project-overview)
2. [Architecture](#2-architecture)
3. [Module Reference](#3-module-reference)
   - [3.1 Core](#31-core)
   - [3.2 ADT Layer](#32-adt-layer)
   - [3.3 Domain Layer](#33-domain-layer)
   - [3.4 I/O Layer](#34-io-layer)
   - [3.5 Utilities](#35-utilities)
4. [Data Flow](#4-data-flow)
5. [Command Dispatch System](#5-command-dispatch-system)
6. [Memory Management](#6-memory-management)
7. [Error Handling](#7-error-handling)
8. [Known Limitations & Technical Debt](#8-known-limitations--technical-debt)

---

## 1. Project Overview

OlympicGM is a single-process, interactive C application that parses Olympic Games CSV datasets and exposes a command-line query interface. It manages three datasets in memory simultaneously — athletes (list), hosts (hash map), and medals (dynamic array) — and provides 12 user-facing commands to filter, query, and display data.

The project was originally written as a monolithic `main.c` with inline command handling and interactive `scanf` prompts. The refactored version separates concerns into a layered architecture, introduces a command dispatch table, and moves argument parsing to the shell tokenizer rather than the individual command handlers.

---

## 2. Architecture

The application is organized into five layers. Each layer only depends on layers below it.

```
┌──────────────────────────────────────────────┐
│                  shell.c                     │
│   REPL loop · line tokenization · dispatch   │
├──────────────────────────────────────────────┤
│                 command.c                    │
│  Command table · argument validation ·       │
│  error formatting · app state mutations      │
├──────────────────────────────────────────────┤
│                  logic.c                     │
│  Queries · filters · aggregations            │
├─────────────────────┬────────────────────────┤
│       load.c        │      listings.c        │
│   CSV parsing       │   Formatted output     │
├─────────────────────┴────────────────────────┤
│          ADT layer (list, map, set)          │
│     Generic data structure implementations   │
└──────────────────────────────────────────────┘
```

### Design Principles

**Separation of concerns** — the shell handles tokenization, `command.c` handles validation and dispatch, `logic.c` handles computation. No layer reaches across more than one level.

**Command table pattern** — commands are registered in a static `command_t[]` array associating a name string, a function pointer, and a description string. Adding a new command requires only a forward declaration, a table entry, and an implementation — no switch statements, no changes to the dispatcher.

**Output vs error separation** — normal output is printed directly from `do_*` functions. Error messages are written to a `msg` buffer and printed by the shell with a uniform `[ERROR]` prefix. This keeps error formatting centralized.

**Inline arguments** — commands receive their arguments tokenized from the input line (`argc`/`argv` style), rather than prompting interactively via `scanf`. This makes commands composable, testable, and consistent.

---

## 3. Module Reference

### 3.1 Core

#### `app.h` / `app.c`

Defines the central application state struct and its lifecycle functions.

```c
typedef struct app_state {
    list_t       *athletes_list;
    map_t        *hosts_map;
    medal_t      *medals_array;
    int           medals_count;
    bool          athletes_loaded;
    bool          medals_loaded;
    bool          hosts_loaded;
} app_state_t;
```

| Function | Description |
|---|---|
| `create_app_state()` | Allocates and initializes the app state. Creates the list and map. Returns `NULL` on failure. |
| `destroy_app_state()` | Frees all heap-allocated members and the struct itself. |

---

#### `command.h` / `command.c`

Implements the command table and dispatcher.

```c
typedef struct {
    const char *name;
    int (*func)(app_state_t *app, int argc, char **argv, char *msg);
    const char *description;
} command_t;
```

| Function | Description |
|---|---|
| `command_dispatch(app, argc, argv, msg)` | Iterates the command table, matches `argv[0]` case-insensitively, and calls the associated handler. Writes an error to `msg` if no match is found. |

Each command handler (`do_*`) follows this contract:

- Returns `CMD_OK` (1), `CMD_ERROR` (< 0), or `CMD_QUIT` (0)
- Validates `argc` before accessing `argv`
- Checks the relevant `*_loaded` flag before accessing data
- Writes human-readable errors to `msg` — never prints errors directly

**Return codes:**

| Code | Value | Meaning |
|---|---|---|
| `CMD_QUIT` | 0 | Shell should terminate |
| `CMD_OK` | 1 | Success |
| `CMD_ERROR` | < 0 | Error — `msg` contains details |

---

#### `logic.h` / `logic.c`

Contains all business logic. Functions in this module are pure computations over the data structures — they do not interact with the shell or command layer.

| Function | Description |
|---|---|
| `filter_list_by_participations(athletes, n)` | Returns a new list of athletes with `games_participations >= n` |
| `filter_list_by_first_year(athletes, year)` | Returns a new list of athletes whose `first_game` ends with the given year string |
| `get_host_data(hosts, edition_name)` | Returns a `char**` array of 4 strings: city, year, country, duration (days) |
| `get_discipline_statistics(medals, size, hosts, edition)` | Returns a `set_t*` of `discipline_stats_t` for the given edition |
| `get_athlete_info(medals, size, athletes, hosts, id, ...)` | Returns a `char**` array of formatted medal lines for the given athlete |
| `get_top_n_countries(medals, size, hosts, athletes, season, start, end, size)` | Returns a `top_n_stats_t*` array of country medal aggregates |
| `get_medals_won(medals, size, hosts, country, start_year, season)` | Prints all medals won by a country from a given year in a given season |

> **Note:** Functions that return heap-allocated arrays (`char**`, `top_n_stats_t*`) transfer ownership to the caller. The caller is responsible for freeing them.

---

### 3.2 ADT Layer

All ADTs are defined as opaque types — the implementation is hidden behind the header interface, allowing the underlying data structure to be swapped without affecting the rest of the codebase.

#### `list.h` — `list_array_list.c`

A generic dynamic array list. Elements are of type `list_elem_t` (defined in `list_elem.h`), which is aliased to `athlete_t`.

Starts with capacity 20, doubles on overflow via `realloc`.

| Key functions | Description |
|---|---|
| `list_create()` | Allocates a new empty list |
| `list_destroy(list**)` | Frees the element array and the struct. Takes a double pointer and sets it to `NULL`. |
| `list_add(list, rank, elem)` | Inserts at position `rank`, shifting elements right |
| `list_get(list, rank, elem*)` | Retrieves element at `rank` by value copy |
| `list_size(list, size*)` | Writes the current element count to `size` |
| `list_clear(list)` | Resets size to 0 without deallocating |

---

#### `map.h` — `map_separate_chaining.c`

A generic hash map using separate chaining for collision resolution. Keys are of type `map_key_t` (`string_wrap_t`), values are of type `map_elem_t` (`host_t`).

| Key functions | Description |
|---|---|
| `map_create()` | Allocates a new empty map |
| `map_destroy(map**)` | Frees all chains, buckets, and the struct |
| `map_put(map, key, value)` | Inserts or updates a key-value pair |
| `map_get(map, key, value*)` | Retrieves a value by key |
| `map_keys(map)` | Returns a heap-allocated array of all keys |
| `map_size(map, size*)` | Writes the current entry count to `size` |

---

#### `set.h` — `set_linked_list.c`

A generic set backed by a linked list. Elements are of type `set_elem_t` (`discipline_stats_t`). Enforces uniqueness on insert.

| Key functions | Description |
|---|---|
| `set_create()` | Allocates a new empty set |
| `set_destroy(set**)` | Frees all nodes and the struct |
| `set_add(set, elem)` | Adds an element if not already present |
| `set_size(set, size*)` | Writes the current element count to `size` |

---

### 3.3 Domain Layer

Plain C structs representing the data model. Each has a corresponding `.c` file with a `print` function used for debugging and listings.

| Struct | Fields |
|---|---|
| `athlete_t` | `athlete_id`, `athlete_name`, `games_participations`, `first_game`, `athlete_birth` |
| `medal_t` | `discipline`, `game`, `event_title`, `gender`, `medal_type`, `participant_type`, `athlete_id`, `country`, `country_code` |
| `host_t` | `game_name`, `season`, `game_year`, `location`, `game_start_date`, `game_end_date` |
| `discipline_stats_t` | `discipline_name`, `top_country`, `participations` |
| `top_n_stats_t` | `country`, `total_medals`, `total_days`, `avg_medals_edition`, `avg_medals_game_days` |

---

### 3.4 I/O Layer

#### `shell.h` / `shell.c`

The REPL (Read-Eval-Print Loop). Reads a line, tokenizes it by space using `strtok`, and calls `command_dispatch`. Prints `[ERROR]` prefixed messages when the return code indicates failure.

```c
void run_shell(app_state_t *app);
```

The shell loop continues until `command_dispatch` returns `CMD_QUIT`.

---

#### `load.h` / `load.c`

CSV parsing for all three datasets. All functions follow the same return code convention.

| Function | Description |
|---|---|
| `import_athletes(list, size*)` | Parses `athletes.csv` into the list |
| `import_medals(array, size*)` | Parses `medals.csv` into a pre-allocated array |
| `import_hosts(map, size*)` | Parses `hosts.csv` into the map |
| `count_file_lines(file*)` | Counts non-header lines in an open file |

> `import_medals` requires a pre-allocated array. The caller (in `command.c`) uses `count_file_lines` to determine the required size before calling it.

**Return codes:**

| Code | Meaning |
|---|---|
| `LOAD_OK` | Success |
| `FILE_NOT_FOUND` | `fopen` returned NULL |
| `LIST_NULL` | List pointer is NULL |
| `MAP_NULL` | Map pointer is NULL |
| `ARRAY_NULL` | Array pointer is NULL |

---

#### `input.h` / `input.c`

Simple standard input helpers. Originally authored by Bruno Silva (ESTSETÚBAL/IPS).

| Function | Description |
|---|---|
| `read_integer(int*)` | Reads and validates an integer from stdin |
| `read_double(double*)` | Reads and validates a double from stdin |
| `read_char(char*)` | Reads a single character from stdin |
| `read_string(char*, size_t)` | Reads a line from stdin, stripping the newline |
| `split_string(char*, int, char*)` | Splits a string by delimiter, returns a heap-allocated `char**` of `n` tokens |

---

#### `listings.h` / `listings.c`

Formatted output and pagination for the shell.

| Function | Description |
|---|---|
| `paginate(list*)` | Displays athletes in pages of `LISTINGS_PAGE_SIZE`, sorted alphabetically in-place |
| `paginate_set(set*)` | Prints all discipline statistics from a set |
| `print_host_details(char**)` | Prints the 4-field host data array |
| `print_athlete_info(...)` | Prints a full athlete profile with medal lines |
| `print_top_n(top_n_stats_t*, size, n)` | Prints the top N rows of a sorted country ranking |
| `sort_list(list*)` | Bubble sort on the list in-place by athlete name. Returns the same pointer. |
| `sort_top_n(top_n_stats_t*, size)` | Bubble sort on the array in-place by total medals descending. Returns the same pointer. |

> **Important:** `sort_list` and `sort_top_n` sort in-place and return the same pointer they receive. Do not free the result separately from the original.

---

### 3.5 Utilities

#### `date.h` / `date.c`

```c
typedef struct { int day; int month; int year; } date_t;
```

| Function | Description |
|---|---|
| `string_to_date(char*, date_t*)` | Parses a date string from the CSV format into a `date_t` struct |

---

#### `string_wrap.h` / `string_wrap.c`

A thin wrapper around a fixed-length char array, used as the map key type to allow value-based equality comparisons in the hash map.

```c
typedef struct { char text[100]; } string_wrap_t;
```

| Function | Description |
|---|---|
| `string_wrap_create(char*)` | Creates a `string_wrap_t` from a C string |

---

## 4. Data Flow

### Loading

```
CSV file → fopen → fgets loop → split_string → domain struct → ADT insert
```

Athletes and hosts are loaded into their ADTs directly. Medals require a pre-allocation step: `count_file_lines` is called first to determine the array size, then `import_medals` fills the array sequentially.

### Querying

```
shell input → tokenize → command_dispatch → do_* → logic function → print
```

Logic functions receive raw pointers to the ADTs from `app_state`. They iterate, filter, or aggregate and return either a new heap-allocated structure or print directly. The command handler is responsible for freeing any returned heap memory.

---

## 5. Command Dispatch System

The dispatcher uses a sentinel-terminated static array of `command_t` structs:

```c
static command_t commands[] = {
    {"load_a", do_load_a, "Loads athlete records from file"},
    // ...
    {NULL, NULL, NULL}  // sentinel
};
```

`command_dispatch` iterates this array and compares `argv[0]` against each `name` field using `strcasecmp` (case-insensitive). On match, it calls the associated function pointer and returns its result directly.

To add a new command:
1. Add a forward declaration at the top of `command.c`
2. Add a row to the `commands[]` table
3. Implement the `do_*` function following the existing pattern

No changes to `shell.c` or any other file are required.

---

## 6. Memory Management

| Structure | Allocated by | Freed by |
|---|---|---|
| `app_state_t` | `create_app_state()` | `destroy_app_state()` |
| `athletes_list` | `list_create()` in `create_app_state` | `do_clear` / `destroy_app_state` |
| `hosts_map` | `map_create()` in `create_app_state` | `do_clear` / `destroy_app_state` |
| `medals_array` | `malloc` in `do_load_m` | `do_clear` / `destroy_app_state` |
| `filtered_list` (show_participations, show_first) | `filter_list_by_*` in `logic.c` | `do_show_participations` / `do_show_first` after use |
| `host_data` (char**) | `get_host_data` in `logic.c` | `do_show_host` after use |
| `medals_statistics` (char**) | `get_athlete_info` in `logic.c` | caller in `do_athlete_info` after use |
| `top_n_list` | `get_top_n_countries` in `logic.c` | caller in `do_topn` after use |
| `split_string` tokens | `split_string` in `input.c` | `load.c` after each parsed line |

> `sort_list` and `sort_top_n` sort in-place and do not allocate new memory. The returned pointer is the same as the input — do not free it separately.

---

## 7. Error Handling

The application uses integer return codes throughout. There is no use of exceptions or `setjmp`.

The shell is the only place that prints error messages to the user. All `do_*` functions write errors into the `msg` buffer (`MAX_MSG_LEN` characters) and return `CMD_ERROR`. The shell then prints `[ERROR] <msg>`.

Normal output (tables, listings, confirmations) is printed directly from the command handlers or the listing functions.

NULL pointer checks are present at the entry point of every ADT function and every logic function, returning an appropriate error code or `NULL` on failure.

---

## 8. Known Limitations & Technical Debt

**In-place sorting** — `sort_list` sorts the `athletes_list` permanently on first `show_all` call. Subsequent loads via `load_a` will re-import in CSV order, but if `show_all` is called again the list is re-sorted.

**`data_loaded` flags are per-dataset but guards are coarse** — some commands check only `athletes_loaded` when they implicitly also need medals to be loaded for full results. This could be tightened.

**($O(n^2)$) and ($O(n^3)$) complexity** — `get_top_n_countries` and `get_athlete_info` contain nested loops over medals, athletes, and hosts. Current implementation uses Bubble Sort ($O(n^2)$) for simplicity; future iterations will implement QuickSort ($O(n \log n)$) to handle larger datasets with sub-second latency.

**`medals_array` pre-allocation** — the array is sized by `count_file_lines`, which counts all lines including blank ones. This may over-allocate slightly but is not a correctness issue.
