#include"GeneratePercentSudoku.hpp"
// ������ַ����Ƿ�ȫ
bool isSafe(const MyVector<int>& board, int row, int col, int num) {
    // 1. �С��С�3x3��Լ������ͨ�����߼���������
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

    // 2. Ʋ�Խ���Լ����i + j ��ȵ��ߣ�������
    int diagSum = row + col;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (i + j == diagSum && (i != row || j != col) && board[i * SIZE + j] == num)
                return false;

    // 3. (2,2)��(4,4)������Լ������2-4����2-4��
    if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                if ((i != row || j != col) && board[i * SIZE + j] == num)
                    return false;
    }

    // 4. (6,6)��(8,8)������Լ������6-8����6-8��
    if (row >= 5 && row <= 7 && col >= 5 && col <= 7) {
        for (int i = 5; i <= 7; i++)
            for (int j = 5; j <= 7; j++)
                if ((i != row || j != col) && board[i * SIZE + j] == num)
                    return false;
    }
    return true;
}

// ��������������̣����ݷ�����generatePercentSudoku���ã�
bool solveSudoku(MyVector<int>& board) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row * SIZE + col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row * SIZE + col] = num;
                        if (solveSudoku(board))
                            return true;
                        board[row * SIZE + col] = 0; // ����
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// ���ɵ�һ�У�������ظ�����generatePercentSudoku���ã�
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

// ���ɰٷֺ��������̣�����generateDiagonalSudoku�Ĺ��ܣ�
void generatePercentSudoku(MyVector<int>& board) {
    for (int i = 0; i < 81; i++)
    {
        board[i] = 0;
    }
    GenerateFirstLine(board);
    solveSudoku(board);
}
