# 🏅 OlympicGM — Olympic Games Manager

A command-line shell application written in **C** for managing and querying Olympic Games data. Load datasets of athletes, medals, and host editions, then query them through an interactive shell interface.

> Originally developed as a university project. Later refactored from scratch for code quality, modularity, and scalability.

---

## Features

- Interactive Unix-style shell with argument-based commands
- Load and manage three independent CSV datasets simultaneously
- Paginated, alphabetically sorted athlete listings
- Filter athletes by participation count or first participation year
- Query host edition details (city, country, duration)
- Discipline statistics per Olympic edition
- Full athlete profile with medal breakdown
- Top N countries ranked by weighted medal score over a season and year range
- Medals won by country from a given year onwards in a given season

---

## Requirements

- GCC (or any C99-compatible compiler)
- GNU Make

---

## Building & Running

```bash
# Build and run
make run

# Build only
make

# Build with debug symbols
make debug

# Clean build artifacts
make clean
```

The Makefile automatically discovers all `.c` files under `src/` — no manual configuration needed when adding new source files.

---

## Data Files

Make sure the following CSV files are under `data/` before running:

| File | Description |
|---|---|
| `data/athletes.csv` | Athlete biographical and participation records |
| `data/medals.csv` | Medal records per athlete per edition |
| `data/hosts.csv` | Olympic edition metadata (city, dates, season) |

---

## Shell Commands

| Command | Description |
|---|---|
| `help [command]` | List all commands, or show usage for a specific one |
| `quit` | Exit the application |
| `load_a` | Load athlete records from `athletes.csv` |
| `load_m` | Load medal records from `medals.csv` |
| `load_h` | Load host records from `hosts.csv` |
| `clear` | Free all loaded data from memory |
| `show_all` | Paginated listing of all athletes (sorted alphabetically) |
| `show_participations <n>` | Athletes with at least `n` participations |
| `show_first <YYYY>` | Athletes whose first participation was in the given year |
| `show_host <City YYYY>` | Details for a given Olympic edition |
| `discipline_statistics <City YYYY>` | Discipline breakdown for a given edition |
| `athlete_info <athleteID>` | Full profile and medal history for an athlete |
| `topn <season> <startYear> <endYear> <n>` | Top N countries by weighted medals in a period |
| `medals_won <country> <year> <season>` | Medals won by a country from a given year onwards |

### Example Session

```
bash@OlympicGM:~$ load_a
75900 athlete records imported.

bash@OlympicGM:~$ load_m
21697 medal records imported.

bash@OlympicGM:~$ load_h
53 host records imported.

bash@OlympicGM:~$ show_host Sydney 2000
Hosting city: Sydney
Year: 2000
Hosting country: Australia
Duration of the event (days): 16

bash@OlympicGM:~$ topn Summer 1990 2010 5
Country                                  | Total medals | Average medals by edition | Average medals by game day
------------------------------------------------------------------------------------------------------------------
United States                            | 2847         | 12.45                     | 3.21
...

bash@OlympicGM:~$ quit
Exiting OlympicGM... See you soon!
```

---

## Project Structure

```
c-olympic-games-manager/
├── include/        # Header files (mirrors src/ structure)
│   ├── adt/        # Abstract Data Type interfaces
│   ├── core/       # App state, command dispatcher, business logic
│   ├── domain/     # Domain model structs
│   ├── io/         # Shell, input, CSV loading, listings
│   └── utils/      # Date parsing, string utilities
├── src/            # Implementations (mirrors include/)
├── data/           # CSV datasets (not versioned)
├── Makefile
└── README.md
```

---

## Documentation
For detailed technical information about architecture, memory management, and design patterns, check the [Technical Manual](docs/Technical%20Manual.md).

## Author

**Filipe Paredes** — [filipeparedes3@gmail.com](mailto:filipeparedes3@gmail.com)

Original university project by Filipe Paredes. List and Map ADT base implementations originally authored by Bruno Silva (brunomnsilva@gmail.com), refactored and extended by Filipe Paredes.
