#include <stdlib.h>
#include <time.h>

void rowAndMaximumOnes(int** mat, int m, int n, int* result) {
    int res = 0, mx = 0; // Store row index and maximum number of ones

    for (int i = 0; i < m; i++) {
        // Convert each row to an integer
        int binaryAsInt = 0;
        for (int j = 0; j < n; j++) {
            binaryAsInt = (binaryAsInt << 1) | mat[i][j]; // Build integer bit by bit
        }

        // Calculate leading zeros
        int leadingZeros = __builtin_clz(binaryAsInt); // Use GCC's built-in clz function
        int validBits = 32 - leadingZeros; // Valid bits = total bits - leading zeros

        // Now count the number of `1`s in the valid bits
        int onesCount = 0;
        for (int j = 0; j < validBits; j++) {
            // Shift right and check if the least significant bit is `1`
            if (binaryAsInt & (1 << (validBits - 1 - j))) {
                onesCount++;
            }
        }

        // Update maximum count and row index
        if (onesCount > mx) {
            mx = onesCount;
            res = i; // Update the row index
        }
    }

    // Return result
    result[0] = res;
    result[1] = mx;
}

// Helper function to count the number of ones in a row
int countOnesInRow(int* row, int n) {
    int count = 0;
    for (int j = 0; j < n; j++) {
        count += row[j];
    }
    return count;
}

// Function to validate the result
int validateResult(int expectedRow, int expectedCount, int actualRow, int actualCount) {
    return (expectedRow == actualRow && expectedCount == actualCount);
}

int main() {
    srand(time(NULL)); // Set random seed

    // Number of test cases
    int testCasesCount = 3;

    for (int t = 0; t < testCasesCount; t++) {
        // Randomly generate number of rows and columns
        int m = rand() % 5 + 1; // Randomly generate number of rows (1 to 5)
        int n = rand() % 5 + 1; // Randomly generate number of columns (1 to 5)

        // Dynamically allocate 2D array
        int** mat = (int**)malloc(m * sizeof(int*));
        for (int i = 0; i < m; i++) {
            mat[i] = (int*)malloc(n * sizeof(int));
        }

        // Randomly generate matrix data (0s and 1s)
        printf("Generated matrix (%d x %d):\n", m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] = rand() % 2; // Randomly generate 0 or 1
                printf("%d ", mat[i][j]); // Output the generated matrix
            }
            printf("\n");
        }

        // Store result
        int result[2];
        rowAndMaximumOnes(mat, m, n, result);
        printf("Row Index: %d, Number of Ones: %d\n", result[0], result[1]);
        
        // Calculate expected result
        int expectedRow = 0;
        int expectedCount = 0;

        for (int i = 0; i < m; i++) {
            int onesCount = countOnesInRow(mat[i], n);
            if (onesCount > expectedCount) {
                expectedCount = onesCount;
                expectedRow = i;
            }
        }

        // Automatically check the result
        if (validateResult(expectedRow, expectedCount, result[0], result[1])) {
            printf("Test Case %d: Passed\n", t + 1);
            printf("\n");
        } else {
            printf("Test Case %d: Failed (Expected: [%d, %d], Got: [%d, %d])\n", 
                   t + 1, expectedRow, expectedCount, result[0], result[1]);
            printf("\n");
        }

        // Free dynamically allocated memory
        for (int i = 0; i < m; i++) {
            free(mat[i]);
        }
        free(mat);
    }

    return 0;
}
