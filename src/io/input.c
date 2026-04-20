/**
 * @file input.c
 *
 * @brief Provides an implementation of input.h.
 * 
 * Relies in always reading text and converting to the appropriate
 * data type. Some straighforward validations are implemented.
 * Does not allow trailing spaces in the formats.
 * 
 * @author Bruno Silva (bruno.silva@estsetubal.ips.pt) - Original Version
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.0.1
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2021 Bruno Silva
 * Modifications and Refactor (c) 2026 Filipe Paredes
 * 
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "io/input.h"

static bool valid_integer_format(const char* s);
static bool valid_double_format(const char* s);
static void remove_newline(char *s);

bool read_integer(int *ptVal) {
	char str[20];
	fgets(str, sizeof(str), stdin);
	remove_newline(str);

	if(!valid_integer_format(str)) return false;

	*ptVal = atoi(str);
	return true;
}

bool read_double(double *ptVal) {
	char str[20];
	fgets(str, sizeof(str), stdin);
	remove_newline(str);

	if(!valid_double_format(str)) return false;

	*ptVal = atof(str);
	return true;
}

bool readChar(char *ptVal) {
	char line[20];
	fgets(line, sizeof(line), stdin);
	remove_newline(line);

    int len = strlen(line);
	/* we only take the fist character */
	if (len > 0) {
		*ptVal = line[0];
		return true;
	}
	return false; /* no characters were read */
}

void read_string(char *charArr, size_t max_size) {
	fgets(charArr, max_size, stdin);
	remove_newline(charArr); /* modifies in-place*/
}

char** split_string(char *string, int nTokens, const char *delim) {
    char **tokens = (char**) malloc(sizeof(char*) * nTokens);
    int index = 0;
    int len = strlen(string);

    // Discard newline, if present
    if (string[len - 1] == '\n') {      
        string[len - 1] = '\0';
        len--;
    }
   
    // Discard carriage return, if present
    if (string[len - 1] == '\r') {      
        string[len - 1] = '\0';
        len--;
    }  
	
    tokens[index++] = &string[0];
    for(int i=0; i < len; i++) {
        if( string[i] == delim[0] ) {
            string[i] = '\0';
            if( i < len - 1 ) {
                tokens[index++] = &string[i] + 1;
            }           
        }
    }
    return tokens;
}

static bool valid_integer_format(const char* s) {
	const char *start = s;
	for(const char *c = s; *c != '\0'; c++) {
		if(c == start && *c == '-') continue;
		if(!isdigit(*c)) return false;
	}
	return true;
}

static bool valid_double_format(const char* s) {
	int dotCount = 0;
	const char *start = s;
	for(const char *c = s; *c != '\0'; c++) {
		if(c == start && *c == '-') continue;
		if(*c == '.') {
			if(dotCount > 0) return false;
			else dotCount++;
			continue;
		}
		if(!isdigit(*c)) return false;
	}
	return true;
}

static void remove_newline(char *s) {
	int len = strlen(s);
	if (len > 0 && s[len - 1] == '\n') {
		s[len - 1] = '\0';
	}
}

