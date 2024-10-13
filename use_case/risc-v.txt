.data
testCasesCount:
        .word   3               # 3 test cases
rows:
        .word   5               # 5 rows
cols:
        .word   6               # 6 cols
result:
        .zero   8               # result[0] stores the row with the most number of ones，result[1] stores the total count of ones
testCases:
        .word   1               # test cases
        .word   0
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   0
        .word   1
        .word   1
        .word   0
        .word   1
        .word   1
        .word   1
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   0
        .word   0
        .word   1
        .word   1
        .word   1
        .word   0
        .word   1
        .word   1
        .word   1
        .word   1
        .word   1
        
#Output the row with the most ones and the number of ones in that row
LC01: .string "Row Index: "
LC02: .string ", Number of Ones: "
LC03: .string "\n"

#If the calculation is correct, output "Passed"
LC11: .string "Test Case "
LC12: .string ": Passed"
LC13: .string "\n "

#If the calculation is wrong, output "Failed", the correct answer and the calculated results
LC21: .string "Test Case "
LC22: .string ": Failed (Expected: ["
LC23: .string ", "
LC24: .string "], Got: ["
LC25: .string ", "
LC26: .string "]) "
LC27: .string "\n"

.text
main:
        addi    sp,sp,-48               # The original data of register
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48                # s0 stores the initial position of sp, allowing sp to be restored to its original position after the program ends
        sw      zero,-20(s0)            # Initialize count = 0
        j       L2

# Call rowAndMaximumOnes function and clz to calculate, and output the results
L8:
        lw      a0,-20(s0)
        jal     ra,rowAndMaximumOnes
        lui     a5,%hi(result)
        addi    a5,a5,%lo(result)
        lw      a4,0(a5)
        lui     a5,%hi(result)
        addi    a5,a5,%lo(result)
        lw      a5,4(a5)
        mv      a2,a5
        mv      a1,a4
        
        # Output the result printf("Row Index: %d, Number of Ones: %d\n", result[0], result[1]);
        la      a0, LC01
        li      a7, 4
        ecall
        mv      a0, a1
        li      a7, 1
        ecall
        la      a0, LC02
        li      a7, 4
        ecall
        mv      a0, a2
        li      a7, 1
        ecall
        la      a0, LC03
        li      a7, 11
        ecall
        
        sw      zero,-24(s0)
        sw      zero,-28(s0)
        sw      zero,-32(s0)
        sw      zero,-32(s0)
        j       L3

# Pass each row of test case data into the countOnesInRow function for calculation
L5:
        lw      a5,-32(s0)
        mv      a4,a5
        slli    a4,a4,1
        add     a4,a4,a5
        slli    a5,a4,3
        mv      a4,a5
        lw      a3,-20(s0)
        mv      a5,a3
        slli    a5,a5,4
        sub     a5,a5,a3
        slli    a5,a5,3
        add     a4,a4,a5
        lui     a5,%hi(testCases)
        addi    a5,a5,%lo(testCases)
        add     a5,a4,a5
        mv      a0,a5
        jal     ra,countOnesInRow               # Call countOnesInRow function
        sw      a0,-36(s0)
        lw      a4,-36(s0)
        lw      a5,-28(s0)
        ble     a4,a5,L4
        lw      a5,-36(s0)
        sw      a5,-28(s0)
        lw      a5,-32(s0)
        sw      a5,-24(s0)
L4:
        lw      a5,-32(s0)
        addi    a5,a5,1                         # row++
        sw      a5,-32(s0)

# Pass each row of test case data into the countOnesInRow function for calculation
L3:
        lui     a5,%hi(rows)
        lw      a5,%lo(rows)(a5)
        lw      a4,-32(s0)
        blt     a4,a5,L5                        # Jump to L5 to execute the countOnesInRow function

        # Call validataResult function to compare the difference between calculated results and the correct answers
        lui     a5,%hi(result)
        addi    a5,a5,%lo(result)
        lw      a4,0(a5)
        lui     a5,%hi(result)
        addi    a5,a5,%lo(result)
        lw      a5,4(a5)
        mv      a3,a5
        mv      a2,a4
        lw      a1,-28(s0)
        lw      a0,-24(s0)
        jal     ra,validateResult
        mv      a5,a0
        beq     a5,zero,L6                      # If the calculated results are identical with the correct answers, output "Passed", otherwise, jump to L6 and ouput "Failed"
        lw      a5,-20(s0)                      # count + 1
        addi    a5,a5,1
        mv      a1,a5
        
        # Output "Passed"，printf("Test Case %d: Passed\n", count + 1);
        la      a0, LC11
        li      a7, 4
        ecall
        mv      a0, a5
        li      a7, 1
        ecall
        la      a0, LC12
        li      a7, 4
        ecall
        la      a0, LC13
        li      a7,11
        ecall
        
        j       L7
L6:
        lw      a5,-20(s0)
        addi    a1,a5,1
        lui     a5,%hi(result)
        addi    a5,a5,%lo(result)
        lw      a4,0(a5)
        lui     a5,%hi(result)
        addi    a5,a5,%lo(result)
        lw      a5,4(a5)
        lw      a3,-28(s0)
        lw      a2,-24(s0)
        
        # Output "Failed", the correct answers and the calculated results printf("Test Case %d: Failed (Expected: [%d, %d], Got: [%d, %d])\n", 
                    count + 1, expectedRow, expectedCount, result[0], result[1]);
        la      a0, LC21
        li      a7, 4
        ecall
        mv      a0, a1
        li      a7, 1
        ecall
        la      a0, LC22
        li      a7, 4
        ecall
        mv      a0, a2
        li      a7, 1
        ecall
        la      a0, LC23
        li      a7, 4
        ecall
        mv      a0, a3
        li      a7, 1
        ecall
        la      a0, LC24
        li      a7, 4
        ecall
        mv      a0, a5
        li      a7, 1
        ecall
        la      a0, LC25
        li      a7, 4
        ecall
         mv      a0, a5
        li      a7, 1
        ecall
        la      a0, LC26
        li      a7, 4
        ecall
        la      a0, LC27
        li      a7,11
        ecall
        
L7:
        lw      a5,-20(s0)                      
        addi    a5,a5,1                         # count++
        sw      a5,-20(s0)
L2:
        lui     a5,%hi(testCasesCount)          # Get the values of testCasesCount 
        lw      a5,%lo(testCasesCount)(a5)
        lw      a4,-20(s0)
        blt     a4,a5,L8                        # 比較 count 和 testCasesCount 的值，count 小於 testCases 的話就跳到 L8
        li      a0,0                            # return 0
        lw      ra,44(sp)                       # ra 取回原本的 return address
        lw      s0,40(sp)                       # s0 取回於 data
        addi    sp,sp,48                        # sp 返回原位
        #jr      ra
        li      a7,10
        ecall

# 利用 clz 的方式快速計算每一列 1 的總數
rowAndMaximumOnes:
        addi    sp,sp,-64
        sw      ra,60(sp)
        sw      s0,56(sp)
        addi    s0,sp,64
        sw      a0,-52(s0)
        sw      zero,-20(s0)                    # Initialiaze res
        sw      zero,-24(s0)                    # Initialiaze mx
        sw      zero,-28(s0)                    # Initialiaze row
        sw      zero,-32(s0)                    # Initialiaze col
        j       L11
L18:
        sw      zero,-36(s0)                    # Initialiaze binaryAsInt
        sw      zero,-32(s0)
        j       L12

# 藉由 slli 和 or 運算將該筆 testCases 中的每一列資料串接成一 unsigned int 的整數
# binaryAsInt = (binaryAsInt << 1) | testCases[count][row][col];
L13:
        lw      a5,-36(s0)
        slli    a2,a5,1
        lui     a5,%hi(testCases)
        addi    a1,a5,%lo(testCases)
        lw      a5,-28(s0)
        lw      a3,-52(s0)
        mv      a4,a5
        slli    a4,a4,1
        add     a4,a4,a5
        slli    a5,a4,1
        mv      a4,a5
        mv      a5,a3
        slli    a5,a5,4
        sub     a5,a5,a3
        slli    a5,a5,1
        add     a4,a4,a5
        lw      a5,-32(s0)
        add     a5,a4,a5
        slli    a5,a5,2
        add     a5,a1,a5
        lw      a5,0(a5)
        or      a5,a2,a5
        sw      a5,-36(s0)

        lw      a5,-32(s0)
        addi    a5,a5,1                         # col++
        sw      a5,-32(s0)
L12:
        lui     a5,%hi(cols)
        lw      a5,%lo(cols)(a5)
        lw      a4,-32(s0)
        blt     a4,a5,L13

        # 初始化 leadingZeros 並呼叫 clz function
        # int leadingZeros = clz(binaryAsInt);
        lw      a5,-36(s0)
        mv      a0,a5
        jal     ra,clz
        sw      a0,-44(s0)

        # 初始化 validBits，有效位數 = 總位數 (32) - 前導 0
        # int validBits = 32 - leadingZeros;
        li      a4,32
        lw      a5,-44(s0)
        sub     a5,a4,a5
        sw      a5,-48(s0)

        # 初始化 onesCount 
        sw      zero,-40(s0)
        sw      zero,-32(s0)
        j       L14

# 針對有效位元一個一個 bit 的檢查是否為 1
L16:
        lw      a5,-48(s0)
        addi    a4,a5,-1
        lw      a5,-32(s0)
        sub     a5,a4,a5
        lw      a4,-36(s0)
        sra     a5,a4,a5
        andi    a5,a5,1
        beq     a5,zero,L15

        # 當有 1 的時候 onesCount++
        lw      a5,-40(s0)
        addi    a5,a5,1
        sw      a5,-40(s0)
L15:
        lw      a5,-32(s0)
        addi    a5,a5,1
        sw      a5,-32(s0)
L14:
        lw      a4,-32(s0)
        lw      a5,-48(s0)
        blt     a4,a5,L16

        # 計算完一列的 1 總數後，與先前的結果比較並更新 res 和 mx 變數，紀錄最多 1 的列和其 1 的總數。
        lw      a4,-40(s0)
        lw      a5,-24(s0)
        ble     a4,a5,L17
        lw      a5,-40(s0)
        sw      a5,-24(s0)
        lw      a5,-28(s0)
        sw      a5,-20(s0)
L17:
        lw      a5,-28(s0)
        addi    a5,a5,1
        sw      a5,-28(s0)
L11:
        lui     a5,%hi(rows)
        lw      a5,%lo(rows)(a5)
        lw      a4,-28(s0)
        blt     a4,a5,L18

        # 該筆 testCases 的每一列都運算完後，將最終結果儲存回 result[0] 以及 result [1]
        lui     a5,%hi(result)
        addi    a5,a5,%lo(result)
        lw      a4,-20(s0)
        sw      a4,0(a5)
        lui     a5,%hi(result)
        addi    a5,a5,%lo(result)
        lw      a4,-24(s0)
        sw      a4,4(a5)
        nop
        lw      ra,60(sp)
        lw      s0,56(sp)
        addi    sp,sp,64
        jr      ra

# clz function，快速計算前導 0 的總數並排除
clz:
        addi    sp,sp,-48
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48
        sw      a0,-36(s0)
        sw      zero,-20(s0)

        # 如果傳進來 clz 的 function 是 0 的話直接回傳 32
        lw      a5,-36(s0)
        bne     a5,zero,L22
        li      a5,32
        j       L21

# 不斷慢慢左移尋找前導 0
L23:
        lw      a5,-20(s0)
        addi    a5,a5,1
        sw      a5,-20(s0)
        lw      a5,-36(s0)
        slli    a5,a5,1
        sw      a5,-36(s0)
L22:
        lw      a5,-36(s0)
        bge     a5,zero,L23
        lw      a5,-20(s0)                      # The end of clz function 
L21:
        mv      a0,a5
        lw      ra,44(sp)
        lw      s0,40(sp)
        addi    sp,sp,48
        jr      ra
                
# 用來計算正確答案的 function，計算每一列 1 的加總
countOnesInRow:
        addi    sp,sp,-48
        sw      ra,44(sp)
        sw      s0,40(sp)
        addi    s0,sp,48
        sw      a0,-36(s0)
        sw      zero,-20(s0)
        sw      zero,-24(s0)
        sw      zero,-24(s0)
        j       L25
L26:
        lw      a5,-24(s0)
        slli    a5,a5,2
        lw      a4,-36(s0)
        add     a5,a4,a5
        lw      a5,0(a5)
        lw      a4,-20(s0)
        add     a5,a4,a5
        sw      a5,-20(s0)
        lw      a5,-24(s0)
        addi    a5,a5,1
        sw      a5,-24(s0)
L25:
        lui     a5,%hi(cols)
        lw      a5,%lo(cols)(a5)
        lw      a4,-24(s0)
        blt     a4,a5,L26
        lw      a5,-20(s0)
        mv      a0,a5
        lw      ra,44(sp)
        lw      s0,40(sp)
        addi    sp,sp,48
        jr      ra
        
# 用以比對正確答案與計算結果的 function
validateResult:
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        addi    s0,sp,32
        sw      a0,-20(s0)
        sw      a1,-24(s0)
        sw      a2,-28(s0)
        sw      a3,-32(s0)
        lw      a4,-20(s0)
        lw      a5,-28(s0)
        bne     a4,a5,L29
        lw      a4,-24(s0)
        lw      a5,-32(s0)
        bne     a4,a5,L29
        li      a5,1
        j       L31
L29:
        li      a5,0
L31:
        mv      a0,a5
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jr      ra