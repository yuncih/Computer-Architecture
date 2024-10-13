#include <stdio.h>
#include <stdlib.h>

void rowAndMaximumOnes(int count);
int clz(unsigned int x);
int countOnesInRow(int* row);
int validateResult(int expectedRow, int expectedCount, int actualRow, int actualCount);

int testCasesCount = 3, rows = 5, cols = 6;
int result[2];
int testCases[3][5][6] = {
    {
        {1,0,0,0,1,1},
        {1,0,0,1,1,1},
        {1,0,0,0,1,1},
        {1,0,0,1,1,1},
        {1,0,0,0,1,1}
    },
    {
        {0,1,1,1,1,1},
        {1,0,0,1,1,1},
        {1,0,0,0,1,1},
        {1,0,0,1,1,1},
        {1,0,0,0,1,1}
    },
    {
        {1,0,0,0,1,1},
        {1,0,0,1,1,1},
        {1,0,0,0,1,1},
        {1,0,0,1,1,1},
        {0,1,1,1,1,1}
    },
};

int main() {
    int count = 0;
    for (count = 0; count < testCasesCount; count++) {
        rowAndMaximumOnes(count);
        printf("Row Index: %d, Number of Ones: %d\n", result[0], result[1]);

        // 計算預期結果
        int expectedRow = 0;
        int expectedCount = 0;

        int row = 0;
        for (row = 0; row < rows; row++) {
            int onesCount = countOnesInRow(testCases[count][row]);
            if (onesCount > expectedCount) {
                expectedCount = onesCount;
                expectedRow = row;
            }
        }

        // 自動檢查結果
        if (validateResult(expectedRow, expectedCount, result[0], result[1])) {
            printf("Test Case %d: Passed\n", count + 1);
            printf("\n");
        } else {
            printf("Test Case %d: Failed (Expected: [%d, %d], Got: [%d, %d])\n", 
                    count + 1, expectedRow, expectedCount, result[0], result[1]);
            printf("\n");
        }
    }
    
    return 0;
}

void rowAndMaximumOnes(int count) {
    int res = 0, mx = 0; // 儲存行的索引和最大 1 的數量
    int row = 0, col = 0;
    for (row = 0; row < rows; row++) {
        // 將每行轉換為整數
        int binaryAsInt = 0;
        for (col = 0; col < cols; col++) {
            binaryAsInt = (binaryAsInt << 1) | testCases[count][row][col]; // 逐位構建整數
        }

        // 計算前導零
        int leadingZeros = clz(binaryAsInt); // 使用 GCC 提供的 clz 函數
        int validBits = 32 - leadingZeros; // 有效位數 = 總位數 - 前導零

        // 現在逐位計算有效位中的 `1` 的數量
        int onesCount = 0;
        for (col = 0; col < validBits; col++) {
            // 右移並檢查最低位是否為 `1`
            if (binaryAsInt & (1 << (validBits - 1 - col))) {
                onesCount++;
            }
        }

        // 更新最大值和行索引
        if (onesCount > mx) {
            mx = onesCount;
            res = row; // 更新行的索引
        }
    }

    // 返回結果
    result[0] = res;
    result[1] = mx;
}

int clz(unsigned int x) {
    int count = 0;

    // 檢查 x 是否為 0
    if (x == 0) {
        return 32; // 假設是 32 位元，則全是零
    }

    // 使用逐位移位的方法來計算前導零
    while ((x & (1U << 31)) == 0) {
        count++;
        x <<= 1; // 將 x 左移一位
    }

    return count;
}


// 計算行中 1 的數量的輔助函數
int countOnesInRow(int* row) {
    int count = 0, col = 0;
    for (col = 0; col < cols; col++) {
        count += row[col];
    }
    return count;
}

// 驗證結果的函數
int validateResult(int expectedRow, int expectedCount, int actualRow, int actualCount) {
    return (expectedRow == actualRow && expectedCount == actualCount);
}