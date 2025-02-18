#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#define MAX_TASK_LENGTH 1024

int main() {
    char task[MAX_TASK_LENGTH];
    char command[MAX_TASK_LENGTH + 50];  // Extra space for the Python command

    // Get the task from user
    printf("Enter your task: ");
    fgets(task, MAX_TASK_LENGTH, stdin);

    // Remove trailing newline if present
    size_t len = strlen(task);
    if (len > 0 && task[len-1] == '\n') {
        task[len-1] = '\0';
    }

    // Construct the command to run the Python script
    // We use printf to pipe the task into the Python script
    snprintf(command, sizeof(command), "echo \"%s\" | python3 main.py", task);

    // Execute the command
    int status = system(command);

    if (status != 0) {
        printf("Error executing Python script\n");
        return 1;
    }

    return 0;
}
