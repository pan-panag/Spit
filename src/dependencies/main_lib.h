/**
 * main_lib.h
 * A header file to manage all dependencies for the main shell program.
 * 
 * This allows me to add all dependencies as their own packages, and then
 * include them all in this one file. This way, I can include only this one file
 * in the main shell program.
 */
#ifndef MAIN_LIB_H
#define MAIN_LIB_H

// Include all standard library dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

// Include all custom dependencies
#include "ansi_formats.h"
#include "./default_lib/default_funcs.h"
#include "./filetree_lib/filetree_funcs.h"

// Define the shell prompt
char *builtin_str[] = {
    "help",
    "clear",
    "exit",
    "dir",
    "ls",
    "cd"
};

// Array of function pointers for built-in commands
int (*builtin_func[]) (char **) = {
    &spit_help,
    &spit_clear,
    &spit_exit,
    &spit_dir,
    &spit_ls,
    &spit_cd
};

// Number of built-in commands
int spit_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

// Built-in command implementation for function: help
int spit_help(char **args) {
    printf("spit shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < spit_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }
    return 1;
}

#endif // MAIN_LIB_H
