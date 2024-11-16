#include "lib.h"

// Define the list of built-in commands
char *builtin_str[] = {
    "help",
    "ls",
    "dir",
    "cd",
    "clear",
    "exit"
};

// Define the corresponding functions
int (*builtin_func[]) (char **) = {
    &spit_help,
    &spit_ls,
    &spit_dir,
    &spit_cd,
    &spit_clear,
    &spit_exit
};

int spit_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

// Implementation of the built-in functions
int spit_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "spit: expected argument to \"cd\"\n");
    } else {
        if (SetCurrentDirectory(args[1]) == 0) {
            perror("spit");
        }
    }
    return 1;
}

int spit_help(char **args) {
    printf("Built-in commands:\n");
    for (int i = 0; i < spit_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }
    return 1;
}

int spit_exit(char **args) {
    return 0; // Return 0 to indicate exit
}

int spit_ls(char **args) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    // Default to current directory if no argument is provided
    char *path = (args[1] == NULL) ? "." : args[1];

    // Create the search pattern
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*", path);

    // Start searching for files
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "spit: dir: cannot access '%s': No such file or directory\n", path);
        return 1;
    } 

    do {
        // Skip the current and parent directory entries
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            printf("%s\n", findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    return 1;
}

int spit_dir(char **args) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    // Default to current directory if no argument is provided
    const char *path = (args[1] == NULL) ? "." : args[1];

    // Create the search pattern
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*", path);

    // Start searching for files
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "spit: dir: cannot access '%s': No such file or directory\n", path);
        return 1; // Indicate failure
    } 

    // Loop through the found files
    do {
        // Print the name of the file or directory
        printf("%s\n", findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind); // Close the handle
    return 1; // Indicate success
}

int spit_clear(char **args) {
    // Get the handle to the console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "spit: clear: unable to get console handle\n");
        return 1; // Indicate failure
    }

    // Get the console screen buffer size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        fprintf(stderr, "spit: clear: unable to get console buffer info\n");
        return 1; // Indicate failure
    }

    // Calculate the number of characters in the buffer
    DWORD consoleSize = csbi.srWindow.Right * csbi.srWindow.Bottom;
    
    // Fill the console buffer with spaces
    DWORD written;
    if (!FillConsoleOutputCharacter(hConsole, ' ', consoleSize, (COORD){0, 0}, &written)) {
        fprintf(stderr, "spit: clear: unable to fill console output\n");
        return 1; // Indicate failure
    }

    // Reset the cursor position to the top left corner
    SetConsoleCursorPosition(hConsole, (COORD){0, 0});

    return 1; // Indicate success
}
