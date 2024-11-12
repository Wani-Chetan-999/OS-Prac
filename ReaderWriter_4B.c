#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    // Accept the size of the array
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array in the parent process
    bubbleSort(arr, n);

    // Print the sorted array
    printf("Sorted Array (Parent): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        sleep(2); // Simulate delay to demonstrate orphan process (if parent exits early)

        // Prepare arguments for execve
        char *args[n + 2];  // +2: One for program name, one for NULL terminator
        args[0] = "./child"; // Name of the executable

        // Convert sorted array to strings
        for (int i = 0; i < n; i++) {
            char *arg = malloc(10); // Allocate memory for string representation
            snprintf(arg, 10, "%d", arr[i]);
            args[i + 1] = arg;
        }

        args[n + 1] = NULL; // NULL terminate the arguments list

        // Use execve to load the child program
        if (execve(args[0], args, NULL) == -1) {
            perror("execve failed");
            // Free allocated memory if execve fails
            for (int i = 1; i <= n; i++) {
                free(args[i]);
            }
        }

    } else {
        // Parent process waits for the child process, with a delay to allow a brief zombie state
        sleep(1); // Short delay to see the child process as a zombie (optional)
        wait(NULL);
        printf("Parent process exiting.\n");
    }

    return 0;
}
