#ifndef LIB_H
#define LIB_H

#include <stdio.h>   // For fprintf and perror
#include <windows.h> // For Windows API functions
#include <stdlib.h>  // For exit


/**
 * Built-in command function declarations
 */
int spit_cd(char **args);
int spit_help(char **args);
int spit_exit(char **args);
int spit_dir(char **args);
int spit_ls(char **args);
int spit_clear(char **args);


/**
 * List of built-in commands,
 * followed by their corresponding functions.
 */
extern char *builtin_str[];  // Declare the array of built-in command strings
extern int (*builtin_func[])(char **);  // Declare the array of function pointers


int spit_num_builtins();  // Declaration of the function to get the number of built-ins

#endif // LIB_H