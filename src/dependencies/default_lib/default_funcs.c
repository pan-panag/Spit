#include "default_funcs.h"

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

int spit_exit(char **args) {
    return 0; // Return 0 to indicate exit
}