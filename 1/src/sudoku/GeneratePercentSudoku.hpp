#pragma once
#include"GenerateSudoku.hpp"

//检查在给定的行、列和数字的情况下，数字是否可以安全地放置在数独棋盘上
bool isSafe(const MyVector<int>& board, int row, int col, int num);
//随机生成数独棋盘
bool solveSudoku(MyVector<int>& board);
//随机生成第一行
void GenerateFirstLine(MyVector<int>& a);
//生成百分号数独
void generatePercentSudoku(MyVector<int>& board);
