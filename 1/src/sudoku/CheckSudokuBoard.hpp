#pragma once
#include"../containers/MyVector.hpp"

bool CheckRow(const MyVector<int>& board, int row,int c, int num) {
    for (int col = 0; col < 9; ++col) {
        if (col!=c&&board[row * 9 + col] == num) {
            return false;
        }
    }
    return true;
}

bool CheckColumn(const MyVector<int>& board, int col,int r, int num) {
    for (int row = 0; row < 9; ++row) {
        if (row!=r&&board[row * 9 + col] == num) {
            return false;
        }
    }
    return true;
}

bool CheckBox(const MyVector<int>& board, int startRow, int startCol,int r,int c ,int num) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if ((startRow + row)!=r && (startCol + col)!=c&&board[(startRow + row) * 9 + (startCol + col)] == num) {
                return false;
            }
        }
    }
    return true;
}

bool CheckBoard(const MyVector<int>& board, int x, int y, int num) {
    // �� (x, y) λ�õ����ָ�Ϊ num �󣬼�����������Ƿ�Ϸ�
    if (num == 0) return true;
    MyVector<int> nowboard = board;
    nowboard[(x - 1) * 9 + y - 1] = num;

    // �����
    if (!CheckRow(nowboard, x - 1,y-1, num)) {
        return false;
    }

    // �����
    if (!CheckColumn(nowboard, y - 1,x-1, num)) {
        return false;
    }

    // ��� 3x3 ����
    int startRow = (x - 1) / 3 * 3;
    int startCol = (y - 1) / 3 * 3;
    if (!CheckBox(nowboard, startRow, startCol,x-1,y-1,num)) {
        return false;
    }

    return true;
}
