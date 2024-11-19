#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "./dependencies/main_lib.h"

#define SPIT_READLINE_BUFSIZE 1024
#define SPIT_TOKEN_BUFSIZE 64
#define SPIT_CWD_BUFSIZE MAX_PATH

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
        
        line = spit_read_line();        // Read a line from stdin
        args = spit_split_line(line);   // Split the line into arguments
        status = spit_execute(args);    // Execute the arguments

        free(line);
        free(args);
    } while (status);
}

char *spit_read_line(void) {
    int bufsize = SPIT_READLINE_BUFSIZE;            // Initial buffer size
    int position = 0;                               // Current position in buffer
    char *buffer = malloc(sizeof(char) * bufsize);  // Allocate buffer
    int c;                                          // Current character

    // Check if buffer was allocated
    if (!buffer) {
        fprintf(stderr, "spit: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // Read a character
        c = getchar();

        if (c == EOF || c == '\n') {
            // If it hits EOF (or user presses ENTER), replace null character and return
            buffer[position] = '\0';
            return buffer;
        } else {
            // Add character to buffer
            buffer[position] = c;
        }
        position++;

        // If buffer size is exceeded reallocate
        if (position >= bufsize) {
            bufsize += SPIT_READLINE_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            // Check if buffer was reallocated
            if (!buffer) {
                fprintf(stderr, "spit: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **spit_split_line(char *line) {
    int bufsize = SPIT_TOKEN_BUFSIZE;                   // Initial buffer size
    int position = 0;                                   // Current position in buffer
    char **tokens = malloc(bufsize * sizeof(char *));   // Allocate buffer
    char *token;                                        // Current token

    // Check if buffer was allocated
    if (!tokens) {
        fprintf(stderr, "spit: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Split line into tokens
    token = strtok(line, SPIT_TOKEN_DELIM);
    while (token != NULL) {
        // Add token to buffer and increment position
        tokens[position] = token;
        position++;

        // If buffer size is exceeded reallocate
        if (position >= bufsize) {
            bufsize += SPIT_TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * (sizeof(char *)));

            // Check if buffer was reallocated
            if (!tokens) {
                fprintf(stderr, "spit: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        // Get next token
        token = strtok(NULL, SPIT_TOKEN_DELIM);     // NULL to continue from previous position
    }
    tokens[position] = NULL;    // Add NULL to end of buffer
    return tokens;
}

int spit_launch(char **args) {
    STARTUPINFO si;             // Process startup information
    PROCESS_INFORMATION pi;     // Process information
    DWORD status;               // Process exit status

    // Initialize memory for STARTUPINFO and PROCESS_INFORMATION structs to zero
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);     // Required size of the structure
    ZeroMemory(&pi, sizeof(pi));

    // Count length of args
    int length = 0;
    for (int i = 0; args [i] != NULL; i++) {
        length += strlen(args[i]) + 1;  // +1 for space
    }

    // Convert args to a single command string for CreateProcess
    char *command = malloc(length);

    // Check if command was allocated
    if (!command) {
        fprintf(stderr, "spit: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Initialize command to empty string
    command[0] = '\0';

    // Concatenate args into command string
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
    int i;      // Loop counter

    if (args[0] == NULL) {
        // An empty command was entered
        return 1;
    }

    // Check if command is a built-in function
    for (i = 0; i < spit_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return spit_launch(args);
}
