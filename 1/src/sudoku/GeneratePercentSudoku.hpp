#pragma once
#include"GenerateSudoku.hpp"

//����ڸ������С��к����ֵ�����£������Ƿ���԰�ȫ�ط���������������
bool isSafe(const MyVector<int>& board, int row, int col, int num);
//���������������
bool solveSudoku(MyVector<int>& board);
//������ɵ�һ��
void GenerateFirstLine(MyVector<int>& a);
//���ɰٷֺ�����
void generatePercentSudoku(MyVector<int>& board);
