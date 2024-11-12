

#include <stdio.h>

int main() {
    int n = 5; // Number of processes
    int m = 3; // Number of resources

    int allocation[5][3] = { { 0, 1, 0 }, { 2, 0, 0 }, { 3, 0, 2 }, { 2, 1, 1 }, { 0, 0, 2 } };
    int max[5][3] = { { 7, 5, 3 }, { 3, 2, 2 }, { 9, 0, 2 }, { 2, 2, 2 }, { 4, 3, 3 } };
    int available[3] = { 3, 3, 2 };

    int finish[5] = {0}; // Array to mark finished processes
    int safe[5]; // Array to store the safe sequence
    int ind = 0;

    // Calculate Need matrix
    int need[5][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Safety algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) { // If resources are sufficient
                    safe[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        available[y] += allocation[i][y];
                    }
                    finish[i] = 1;
                }
            }
        }
    }

    // Check if a safe sequence was found
    if (ind == n) {
        printf("SAFE Sequence is: ");
        for (int i = 0; i < n - 1; i++) {
            printf("P%d -> ", safe[i]);
        }
        printf("P%d\n", safe[n - 1]);
    } else {
        printf("No SAFE Sequence exists\n");
    }

    return 0;
}
