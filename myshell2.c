#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100  // Define the maximum input size

char* isValidCommand(char* cmd);  // Function declaration to check if a command is valid

int main(int argc, const char* argv[]) {
    char input[MAX];  // Array to store the user input
    char* command;  // Pointer to store the command
    char* args[MAX];  // Array to store arguments

    while (1) {  // Start an infinite loop to keep the shell running
        printf("shell> ");  // Prompt for user input

        fgets(input, MAX, stdin);  // Read the user input from stdin

        input[strcspn(input, "\n")] = '\0';  // Remove the newline character from the input

        // Tokenize the input into command and arguments
        int i = 0;
        command = strtok(input, " \t");  // Get the first token (command)
        while (command != NULL && i < MAX - 1) {  // Tokenize and store the arguments
            args[i++] = command;
            command = strtok(NULL, " \t");  // Get the next token
        }
        args[i] = NULL;  // Null-terminate the array of arguments

        if (i == 0) {  // If no command was entered, continue to the next iteration
            continue;
        }

        // Handle "leave" command to exit the shell
        if (strcmp(args[0], "leave") == 0) {
            exit(0);  // Exit the program
        }

        // Handle "cd" command to change the directory
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {  // If no argument is provided
                char* homeDir = getenv("HOME");  // Get the HOME environment variable
                if (homeDir == NULL) {  // If HOME is not set, print an error
                    fprintf(stderr, "cd: HOME not set\n");
                }
                else if (chdir(homeDir) != 0) {  // Change to the HOME directory
                    perror("cd failed");
                }
            }
            else if (chdir(args[1]) != 0) {  // If an argument is provided, change to the specified directory
                perror("cd failed");
            }
            continue;  // Skip the rest of the loop after handling "cd"
        }

        // Check if the command is valid
        char* filePath = isValidCommand(args[0]);
        if (filePath == NULL) {  // If the command is not found
            printf("Error: Command not found\n");
            continue;  // Skip the rest of the loop
        }

        pid_t pid = fork();  // Create a new process
        if (pid < 0) {  // If fork fails
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0) {  // In the child process
            execv(filePath, args);  // Execute the command
            perror("execv failed");  // If execv fails
            exit(1);
        }
        else {  // In the parent process
            wait(NULL);  // Wait for the child process to finish
        }
    }
    return 0;  // Exit the program
}

// Function to check if the command is valid
char* isValidCommand(char* cmd) {
    char* pathVar = getenv("PATH");  // Get the PATH environment variable
    if (!pathVar) {  // If PATH is not set, return NULL
        return NULL;
    }

    char pathCopy[MAX];  // Array to hold the copy of PATH
    strcpy(pathCopy, pathVar);  // Copy PATH to avoid modifying the original
    char* tempDir = strtok(pathCopy, ":");  // Tokenize PATH by ":"
    static char filePath[MAX];  // Array to store the full file path

    // First, check the current directory (".") for the command
    snprintf(filePath, sizeof(filePath), "./%s", cmd);  // Create the full path for the current directory
    if (access(filePath, X_OK) == 0) {  // If the command exists and is executable
        return strdup(filePath);  // Return the full path as a duplicate string
    }

    // Now, check other directories in the PATH variable
    while (tempDir != NULL) {  // For each directory in PATH
        snprintf(filePath, sizeof(filePath), "%s/%s", tempDir, cmd);  // Construct the full path
        if (access(filePath, X_OK) == 0) {  // If the command exists and is executable
            return strdup(filePath);  // Return the full path as a duplicate string
        }
        tempDir = strtok(NULL, ":");  // Get the next directory in PATH
    }
    return NULL;  // If the command was not found in any directory, return NULL
}
