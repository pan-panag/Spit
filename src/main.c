#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "./dependencies/main_lib.h"

#define SPIT_READLINE_BUFSIZE 1024
#define SPIT_TOKEN_BUFSIZE 64
#define SPIT_CWD_BUFSIZE 1024

#define SPIT_TOKEN_DELIM " \t\r\n\a"


void spit_loop(void);
char *spit_read_line(void);
char **spit_split_line(char *line);
int spit_launch(char **args);
int spit_execute(char **args);


int main(int argc, char **argv) {
    // Load necessary files

    // Run command loop
    spit_loop();
    // Perform shutdown and cleanup
    printf("Exiting...\n");
    return EXIT_SUCCESS;
}


void spit_loop(void) {
    char *line;
    char **args;
    int status;

    char *cwd = malloc(SPIT_CWD_BUFSIZE);

    do {
        // Get the current working directory
        if (!GetCurrentDirectory(SPIT_CWD_BUFSIZE, cwd)) {
            fprintf(stderr, "spit: GetCurrentDirectory failed (%ld).\n", GetLastError());
            exit(EXIT_FAILURE);
        }

        printf(BOLD_BRIGHT_YELLOW "%s>" RESET, cwd);
        line = spit_read_line();
        args = spit_split_line(line);
        status = spit_execute(args);

        free(line);
        free(args);
    } while (status);
}

char *spit_read_line(void) {
    int bufsize = SPIT_READLINE_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "spit: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we exceed buffer size we need to reallocate
        if (position >= bufsize) {
            bufsize += SPIT_READLINE_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            if (!buffer) {
                fprintf(stderr, "spit: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **spit_split_line(char *line) {
    int bufsize = SPIT_TOKEN_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "spit: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SPIT_TOKEN_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += SPIT_TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * (sizeof(char *)));

            if (!tokens) {
                fprintf(stderr, "spit: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, SPIT_TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int spit_launch(char **args) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD status;

    // Initialize memory for STARTUPINFO
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Count length of args
    int length = 0;
    for (int i = 0; args [i] != NULL; i++) {
        length += strlen(args[i]) + 1;
    }

    // Convert args to a single command string for CreateProcess
    char *command = malloc(length);
    if (!command) {
        fprintf(stderr, "spit: allocation error\n");
        exit(EXIT_FAILURE);
    }
    command[0] = '\0';

    // Concatenate args
    for (int i = 0; args[i] != NULL; i++) {
        strcat(command, args[i]);
        strcat(command, " ");
    }
    // Create the process
    if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("spit: CreateProcess failed (%ld).\n", GetLastError());
        free(command);
        return 1;
    }

    // Wait for the child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get the exit status of the child process
    GetExitCodeProcess(pi.hProcess, &status);

    // Close handles to the process and thread
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    free(command);

    return 1;
}

int spit_execute(char **args) {
    int i;

    if (args[0] == NULL) {
        // An empty command was entered
        return 1;
    }

    for (i = 0; i < spit_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return spit_launch(args);
}
