#include "filetree_funcs.h"

int spit_cd(char **args) {

    // Check if the user provided an argument
    if (args[1] == NULL) {
        fprintf(stderr, "spit: expected argument to \"cd\"\n");
    } else {
        // Attempt to change the current directory
        if (SetCurrentDirectory(args[1]) == 0) {
            fprintf(stderr, "spit: cd: cannot access '%s': No such file or directory\n", args[1]);
        }
    }
    return 1;
}

int spit_ls(char **args) {
    WIN32_FIND_DATA findFileData;   // Structure to hold file information
    HANDLE hFind;                   // Handle to the file search

    // Default to current directory if no argument is provided
    char *path = (args[1] == NULL) ? "." : args[1];

    // Create the search pattern
    char searchPath[MAX_PATH];                                  // Buffer to hold the search path
    snprintf(searchPath, sizeof(searchPath), "%s\\*", path);    // Create the search pattern

    // Start searching for files
    hFind = FindFirstFile(searchPath, &findFileData);

    // Check if the search failed
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "spit: dir: cannot access '%s': No such file or directory\n", path);
        return 1;
    } 

    // Loop through the found files
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
