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

// Function to perform Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements to sort: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("\n[Child Process] Performing Insertion Sort...\n");
        insertionSort(arr, n);
        printf("[Child Process] Sorted Array: ");
        printArray(arr, n);

        // Making child sleep to demonstrate orphan process
        printf("[Child Process] Sleeping for 5 seconds to become orphan...\n");
        sleep(5);
        printf("[Child Process] Exiting...\n");
        exit(0);
    } else {
        // Parent process
        printf("\n[Parent Process] Performing Bubble Sort...\n");
        bubbleSort(arr, n);
        printf("[Parent Process] Sorted Array: ");
        printArray(arr, n);

        // Demonstrating Zombie state
        printf("[Parent Process] Waiting for Child Process to complete...\n");
        wait(NULL);
        printf("[Parent Process] Child Process finished. Checking for Zombie state...\n");

        // Sleep for a while to observe the child in Zombie state
        sleep(10);
        printf("[Parent Process] Exiting...\n");
    }

    return 0;
}