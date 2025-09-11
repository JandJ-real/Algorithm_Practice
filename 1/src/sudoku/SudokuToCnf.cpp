
#include"../definition.h"
#include"../containers/MyVector.hpp"

/***********************************************
*�������ƣ�sudokuToCnf
* �������ܣ�������������ת��Ϊ CNF ��ʽ��������д���ļ���
* ע�ͣ�- ��Դ�ļ� "SudokuBase.cnf" ���ƻ���Լ�����ݡ�
        - ��������������������ֵ�Լ����
        - д�����Խ��ߺ͸��Խ��߲����ظ��Ĺ���
        - д�� CNF �ļ�ͷ��
* ����ֵ��bool���ͣ�����ɹ����� CNF �ļ����򷵻� true�����򷵻� false��
************************************************/
bool SudokuToCnf(const MyVector<int>& board,int empty)
{
    string sourceFilename = "sudoku/SudokuBase.cnf";
    string destinationFilename = "sudoku/NormalSudoku.cnf";

    // ��Դ�ļ����ж�ȡ
    ifstream sourceFile(sourceFilename, ios::binary);
    if (!sourceFile) {
        cerr << "�޷���Դ�ļ� " << sourceFilename << endl;
        return false;
    }

    // ��Ŀ���ļ�����д�룬����ļ����������½�
    ofstream destinationFile(destinationFilename, std::ios::out | std::ios::trunc);
    if (!destinationFile) {
        cerr << "�޷���Ŀ���ļ� " << destinationFilename << endl;
        return false;
    }
    destinationFile << "p" << " " << "cnf" << " " << 729 << " " << 8829 + 81 - empty << endl;
    // ��Դ�ļ���ȡ���ݲ�д�뵽Ŀ���ļ�
   
    for (int i = 1; i <=9; ++i) {
        for (int j = 1; j <=9; ++j) {
            if (board[(i- 1) * 9 + j - 1]) {
				destinationFile << i << j << board[(i - 1) * 9 + j - 1] << " 0" << endl;
            }
        }
    }
    char buffer[1024];
    while (sourceFile.read(buffer, sizeof(buffer))) {
        destinationFile.write(buffer, sourceFile.gcount());
    }

    // д��ʣ������ݣ�����еĻ���
    if (sourceFile.gcount() > 0) {
        destinationFile.write(buffer, sourceFile.gcount());
    }

    // �ر��ļ�
    sourceFile.close();
    destinationFile.close();

    //cout << "�ļ����ݸ�����ɡ�" << endl;
    return true;

}

/***********************************************
*�������ƣ�XsudokuToCnf
* �������ܣ�������������(X����)ת��Ϊ CNF ��ʽ��������д���ļ���
* ע�ͣ�- ��Դ�ļ� "SudokuBase.cnf" ���ƻ���Լ�����ݡ�
        - ��������������������ֵ�Լ����
        - д�����Խ��ߺ͸��Խ��߲����ظ��Ĺ���
        - д�� CNF �ļ�ͷ��
* ����ֵ��bool���ͣ�����ɹ����� CNF �ļ����򷵻� true�����򷵻� false��
************************************************/
bool XSudokuToCnf(const MyVector<int>& board, int empty)
{
    string sourceFilename = "sudoku/SudokuBase.txt";
    string destinationFilename = "sudoku/XSudoku.txt";

    // ��Դ�ļ����ж�ȡ
    ifstream sourceFile(sourceFilename, ios::binary);
    if (!sourceFile) {
        cerr << "�޷���Դ�ļ� " << sourceFilename << endl;
        return false;
    }

    // ��Ŀ���ļ�����д�룬����ļ����������½�
    ofstream destinationFile(destinationFilename, std::ios::out | std::ios::trunc);
    if (!destinationFile) {
        cerr << "�޷���Ŀ���ļ� " << destinationFilename << endl;
        return false;
    }

	// д���ļ�ͷ
    destinationFile << "p" << " " << "cnf" << " " << 729 << " " << 8829 +648+81 - empty << endl;

    // ���Խ��߲����ظ��Ĺ���
    int mainDiagonal[9] = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    for (int z = 1; z <= 9; ++z) {
        for (int i = 0; i < 9; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                destinationFile << 0 - (mainDiagonal[i] * 10 + z) << " " << 0 - (mainDiagonal[j] * 10 + z) << " " << 0 << endl;
            }
        }
    }

    // ���Խ��߲����ظ��Ĺ���
    int antiDiagonal[9] = { 19, 28, 37, 46, 55, 64, 73, 82, 91 };
    for (int z = 1; z <= 9; ++z) {
        for (int i = 0; i < 9; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                destinationFile << 0 - (antiDiagonal[i] * 10 + z) << " " << 0 - (antiDiagonal[j] * 10 + z) << " " << 0 << endl;
            }
        }
    }
//�������������ֲ�����Լ��----------------------------------------
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            if (board[(i - 1) * 9 + j - 1]) {
                destinationFile << i << j << board[(i - 1) * 9 + j - 1] << " 0" << endl;
            }
        }
    }
//�������������ֲ�����Լ��---------------------------------------
//���ƻ���Լ������-----------------------------------------------
    char buffer[1024];
    while (sourceFile.read(buffer, sizeof(buffer))) {
        destinationFile.write(buffer, sourceFile.gcount());
    }
    // д��ʣ������ݣ�����еĻ���
    if (sourceFile.gcount() > 0) {
        destinationFile.write(buffer, sourceFile.gcount());
    }
//���ƻ���Լ������-----------------------------------------------

    // �ر��ļ�
    sourceFile.close();
    destinationFile.close();
    return true;
}

bool PercentSudokuToCnf(const MyVector<int>& board, int empty)
{
    string sourceFilename = "sudoku/SudokuBase.cnf";
    string destinationFilename = "sudoku/PercentSudoku.cnf";

    // ��Դ�ļ����ж�ȡ
    ifstream sourceFile(sourceFilename, ios::binary);
    if (!sourceFile) {
        cerr << "�޷���Դ�ļ� " << sourceFilename << endl;
        return false;
    }

    // ��Ŀ���ļ�����д�룬����ļ����������½�
    ofstream destinationFile(destinationFilename, std::ios::out | std::ios::trunc);
    if (!destinationFile) {
        cerr << "�޷���Ŀ���ļ� " << destinationFilename << endl;
        return false;
    }

	// д���ļ�ͷ
    destinationFile << "p" << " " << "cnf" << " " << 729 << " " << 8829 +972+81 - empty << endl;

    

    // ���Խ��߲����ظ��Ĺ���
    int antiDiagonal[9] = { 19, 28, 37, 46, 55, 64, 73, 82, 91 };
    for (int z = 1; z <= 9; ++z) {
        for (int i = 0; i < 9; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                destinationFile << 0 - (antiDiagonal[i] * 10 + z) << " " << 0 - (antiDiagonal[j] * 10 + z) << " " << 0 << endl;
            }
        }
    }
    
    // �ϰٷֺ� 
    int Space1[9] = { 22, 23, 24, 32, 33, 34, 42, 43, 44 };
    for (int z = 1; z <= 9; ++z) {
        for (int i = 0; i < 9; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                destinationFile << 0 - (Space1[i] * 10 + z) << " " << 0 - (Space1[j] * 10 + z) << " " << 0 << endl;
            }
        }
    }// �°ٷֺ�
    int Space2[9] = { 66, 67, 68, 76, 77, 78, 86, 87, 88 };
    for (int z = 1; z <= 9; ++z) {
        for (int i = 0; i < 9; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                destinationFile << 0 - (Space2[i] * 10 + z) << " " << 0 - (Space2[j] * 10 + z) << " " << 0 << endl;
            }
        }
    }
//�������������ֲ�����Լ��----------------------------------------
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            if (board[(i - 1) * 9 + j - 1]) {
                destinationFile << i << j << board[(i - 1) * 9 + j - 1] << " 0" << endl;
            }
        }
    }
//�������������ֲ�����Լ��---------------------------------------
//���ƻ���Լ������-----------------------------------------------
    char buffer[1024];
    while (sourceFile.read(buffer, sizeof(buffer))) {
        destinationFile.write(buffer, sourceFile.gcount());
    }
    // д��ʣ������ݣ�����еĻ���
    if (sourceFile.gcount() > 0) {
        destinationFile.write(buffer, sourceFile.gcount());
    }
//���ƻ���Լ������-----------------------------------------------

    // �ر��ļ�
    sourceFile.close();
    destinationFile.close();
    return true;
}

