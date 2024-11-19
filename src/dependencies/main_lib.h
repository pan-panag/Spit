#ifndef MAIN_LIB_H
#define MAIN_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "ansi_formats.h"
#include "./default_lib/default_funcs.h"
#include "./filetree_lib/filetree_funcs.h"

char *builtin_str[] = {
    "help",
    "clear",
    "exit",
    "dir",
    "ls",
    "cd"
};

int (*builtin_func[]) (char **) = {
    &spit_help,
    &spit_clear,
    &spit_exit,
    &spit_dir,
    &spit_ls,
    &spit_cd
};

int spit_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

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
