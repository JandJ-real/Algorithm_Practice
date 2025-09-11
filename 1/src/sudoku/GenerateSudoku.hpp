#pragma once
#include"../containers/MyVector.hpp"
#define SIZE 9
//��������
typedef struct
{
    int base_col; // ��ǰ�е���ʼ������
    int curr_col; // ʵ�ʴ洢��
    unsigned int col_mask;//��¼ǰ���е����ݣ��������ǰ��ʵ�ʿ��е�λ��
} Col_Index;//ĳһ�е����ݽṹ������ǰ�������е����ݣ��������ǰ��ʵ�ʿ��е�λ�ã�����Ե�ǰ�е�����

typedef struct {
    int long_row; // ��ǰ�������ڼ��У��ĸ����ֵ���һ�У���81Ϊ�������
    Col_Index col_index[81]; //ÿһ�е�ʵ������״̬
} Sudoku;//��������

void InitSudoku(Sudoku* sudoku);//��ʼ������
bool isSudokuInProgress(const Sudoku* sudoku);//�ж������Ƿ����
void moveNextRow(Sudoku* sudoku);//������һ��
void rollback_row(Sudoku* sudoku);//�ع�����һ��
int calcRandCol(void);//���������
int calNextCol(int col);//������һ��
 void calculateColumnMaskForRow(Sudoku* sudoku, int long_row);//����������
bool moveNextCol(Sudoku* sudoku);//������һ��
void SaveSudokutoBoard(Sudoku* sudoku, MyVector<int>& Board);//��������������
void PrintBoard(const MyVector<int>& Board);//��ӡ����
void StartSudokuGenerate(Sudoku* sudoku, MyVector<int>& Board);//��ʼ��������
void shuffleArray(MyVector<int>& array);//��������
int generateGameBoard(const MyVector<int>& normalBoard, MyVector<int>& gameBoard);//�ڶ�


