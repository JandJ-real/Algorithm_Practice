#include"GeneratePercentSudoku.hpp"
// 检查数字放置是否安全
bool isSafe(const MyVector<int>& board, int row, int col, int num) {
    // 1. 行、列、3x3宫约束（普通数独逻辑，保留）
    for (int x = 0; x < SIZE; x++) {
        if (board[row * SIZE + x] == num || board[x * SIZE + col] == num)
            return false;
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[(startRow + i) * SIZE + (startCol + j)] == num)
                return false;

    // 2. 撇对角线约束（i + j 相等的线，保留）
    int diagSum = row + col;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (i + j == diagSum && (i != row || j != col) && board[i * SIZE + j] == num)
                return false;

    // 3. (2,2)到(4,4)正方形约束（行2-4，列2-4）
    if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                if ((i != row || j != col) && board[i * SIZE + j] == num)
                    return false;
    }

    // 4. (6,6)到(8,8)正方形约束（行6-8，列6-8）
    if (row >= 5 && row <= 7 && col >= 5 && col <= 7) {
        for (int i = 5; i <= 7; i++)
            for (int j = 5; j <= 7; j++)
                if ((i != row || j != col) && board[i * SIZE + j] == num)
                    return false;
    }
    return true;
}

// 随机生成数独棋盘（回溯法，供generatePercentSudoku调用）
bool solveSudoku(MyVector<int>& board) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row * SIZE + col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row * SIZE + col] = num;
                        if (solveSudoku(board))
                            return true;
                        board[row * SIZE + col] = 0; // 回溯
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// 生成第一行（随机不重复，供generatePercentSudoku调用）
void GenerateFirstLine(MyVector<int>& a) {
    for (int i = 0; i < SIZE; ++i) {
        a[i] = rand() % SIZE + 1;
        int j = 0;
        while (j < i) {
            if (a[i] == a[j]) {
                a[i] = rand() % SIZE + 1;
                j = 0;
            } else j++;
        }
    }
}

// 生成百分号数独棋盘（类似generateDiagonalSudoku的功能）
void generatePercentSudoku(MyVector<int>& board) {
    for (int i = 0; i < 81; i++)
    {
        board[i] = 0;
    }
    GenerateFirstLine(board);
    solveSudoku(board);
}
