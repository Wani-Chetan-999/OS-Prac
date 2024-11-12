#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 2) {
        printf("No elements to display in reverse order.\n");
        return 1;
    }

    // Print array in reverse order
    printf("Array in Reverse Order (Child): ");
    for (int i = argc - 1; i >= 1; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}
