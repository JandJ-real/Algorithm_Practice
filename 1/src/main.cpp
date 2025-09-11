#include"containers/MyVector.hpp"

#include "parser/parser.hpp"

#include"solver/DPLLSolver.hpp"

#include"definition.h"

#include"core/Literal.hpp"//����
#include"core/Clause.hpp"//�Ӿ�(����֮��)
#include"core/CNF.hpp"//�Ӿ�֮��

#include"sudoku/GeneratePercentSudoku.hpp"
#include"sudoku/CheckSudokuBoard.hpp"
#include<iostream>
bool SudokuToCnf(const MyVector<int>& board,int empty);
bool PercentSudokuToCnf(const MyVector<int>& board, int empty);//���Խ�������ת��ΪCNF

using namespace std;
// ȫ�� VSIDS ��ر���
MyVector<double> vsids_score;     // �����÷ֱ����� 1 ~ numVars ��Ӧ���� 1 ~ numVars
int vsids_decay_counter = 0;      // ���ڿ���˥��Ƶ��
const int VSIDS_DECAY_EVERY = 10; // ÿ 10 �ε��� VSIDS ʱ˥��һ�Σ��ɵ�����
const double VSIDS_DECAY_FACTOR = 0.5; // ˥��ϵ�������� 0.5 ��ʾ�÷ּ���


int Count=0;
int numVars=0;
int numClauses=0;
int isread=0;
clock_t start_clock;//��ʼʱ����
clock_t end_clock;//����ʱ����
double time_ms=0;//����ʱ�� 
double time_ms_o=0;//��Ϊ�Ƚϵĳ�ʼ����ʱ�� 
int main()
{
	int choice=1;
	int choice2=1;
	int choice3=1;
	int choice4=1;
	int way=1;
	 
	std::string filename;
	CNF cnf;
	int *assignments=nullptr;
	double time1=0,time2=0;
	Sudoku* sudoku=new Sudoku;
	MyVector<int> NormalBoard(81, 0);
	MyVector<int> GameBoard(81, 0);
	MyVector<int> GamePlayBoard(81, 0);
	int empty=0;
	int x=0,y=0,num=0;
	
	srand(static_cast<unsigned int>(time(nullptr)));//���������
    while(true)
    {
    	cout<<endl<<endl;
    	cout<<"1. SAT  2. Sudoku"<<endl;
    	cout<<"0. Exit"<<endl;
    	cin >> choice;
    	switch(choice)
	    {
	    	case 1:
		    	choice2=1;
		    	isread=0;
		    	while(choice2)
		    	{
		    		
		    		cout << "SAT���"<<endl;
		    		cout << "1. ��ȡCNF�ļ�  2.��ӡCNF�ļ�"<<endl;
		    		cout << "3. ���CNF�ļ�"<<endl;
			    	cout << "0. ����"<<endl;
				
			    	cin >> choice2;
				
			    	switch(choice2)
			    	{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				    	case 1:
				    		isread=0;
				    		cout << "�����ļ�·��" << endl;
				    		cin >> filename;
						
				    		if(CNFParser::parse(cnf,filename,numVars,numClauses))
				    		{
				    			cout << "��ȡ�ɹ�" << endl;
				    			isread=1;
				    			//��ʼ��������
				    			vsids_score = MyVector<double>(numVars + 1, 0.0);  // 1-based indexing
				    			if(assignments!=nullptr) delete[] assignments;
				    			assignments = new int[numVars+1]; 
				    		}
				    		time_ms_o=0;
				    		//����������� 
				    		system("pause");
				    		system("cls");
					    	break;
						
				    	case 2:
				    		if(!isread)
					    	{
					    		cout << "�ļ�δ��ȡ,���ȡ������" << endl;
							
					    	}
					    	else if(cnf.empty()) cout << "CNFΪ��" << endl;
					    	else cnf.print();
					    	system("pause");
					    	system("cls");
					    	break;
						
				    	case 3:
				    		Count=0;
				    		way=1;
				    		cout<<"isread: "<<isread <<" way:"<<way<<endl;
				    		while(isread && way)
					    	{
					    		Count=0;
					    		cout << "��ѡ���֧��Ԫѡȡ����"<<endl;
					    		cout << "1. ѡ���׸���Ԫ" << endl;
					    		cout << "2. ѡ��������ı�Ԫ1"<<endl;
					    		cout << "3. ѡ��������ı�Ԫ2"<<endl;
					    		cout << "4. ��jw����ѡ��Ȩ����ߵı�Ԫ"<<endl; 
					    	
					    		cout << "0. ����"<<endl; 
					    		cin >> way; 
					    		//��¼DPLLִ��ǰ����ʼʱ���� 
					    		start_clock = clock();
					    		
					    		bool res=DPLL(cnf,way,assignments);
					    		//��¼ִ�к�Ľ���ʱ���� 
					    		end_clock = clock(); 
					    		//��������ʱ��
					    		if(way==1)
					    		{
					    			time_ms_o=(double)(end_clock - start_clock) * 1000.0 / CLOCKS_PER_SEC; 
								}
								else
								{
									time_ms=(double)(end_clock - start_clock) * 1000.0 / CLOCKS_PER_SEC;
								}
								if(way==1)
								{
									
								}
								
								 
					    		switch(way)
					    		{
							    	case 1:
									
								    	if(res)
								    	{
									    	cout<<"�ɽ�!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "���ɽ�!" << endl;
								    	printf("ִ��ʱ��Ϊ%.2f ms\n", time_ms_o);
										saveResultToFile(filename, res, assignments, time_ms_o); 
								    	system("pause");
								    	system("cls");
								    	break;
								     
								    case 2:
								    	if(res)
								    	{
									    	cout<<"�ɽ�!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "���ɽ�!" << endl;
								    	printf("ִ��ʱ��Ϊ%.2f ms\n", time_ms);
								    	if(time_ms_o!=0)
								    	{
								    	    cout << "ʱ���Ż���Ϊ" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
								    	saveResultToFile(filename, res, assignments, time_ms); 
										 
								    	system("pause");
								    	system("cls");
								    	break;
								    case 3:
								    	if(res)
								    	{
									    	cout<<"�ɽ�!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "���ɽ�!" << endl;
								    	printf("ִ��ʱ��Ϊ%.2f ms\n", time_ms);
										if(time_ms_o!=0)
								    	{
								    	    cout << "ʱ���Ż���Ϊ" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
										saveResultToFile(filename, res, assignments, time_ms);
								    	system("pause");
								    	system("cls");
								    	break;
									case 4:
								    	if(res)
								    	{
									    	cout<<"�ɽ�!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "���ɽ�!" << endl;
								    	printf("ִ��ʱ��Ϊ%.2f ms\n", time_ms);
										if(time_ms_o!=0)
								    	{
								    	    cout << "ʱ���Ż���Ϊ" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
										saveResultToFile(filename, res, assignments, time_ms);
								    	system("pause");
								    	system("cls");
								    	break;	
									case 5:
								    	if(res)
								    	{
									    	cout<<"�ɽ�!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "���ɽ�!" << endl;
								    	printf("ִ��ʱ��Ϊ%.2f ms\n", time_ms);
										if(time_ms_o!=0)
								    	{
								    	    cout << "ʱ���Ż���Ϊ" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
										saveResultToFile(filename, res, assignments, time_ms);
								    	system("pause");
								    	system("cls");
								    	break;	
									case 6:
								    	if(res)
								    	{
									    	cout<<"�ɽ�!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "���ɽ�!" << endl;
								    	printf("ִ��ʱ��Ϊ%.2f ms\n", time_ms);
										if(time_ms_o!=0)
								    	{
								    	    cout << "ʱ���Ż���Ϊ" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
										saveResultToFile(filename, res, assignments, time_ms);
								    	system("pause");
								    	system("cls");
								    	break;			
							    	case 0:
							    		
							    		system("cls");
								    	break;
							    	default:
								    	break;
						    	}
					    	}
					    	if(!isread)
						    {
					    		cout << "�ļ�δ��ȡ,���ȡ������" << endl;
						        system("pause");
					    	    system("cls");
					    	}
					    	cout<<1<<endl;
					    	break;
				    	case 0:
				    		
				    		system("pause");
					    	system("cls");
					    	break;
			    	}
			    	
		    	}
		    	break;




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		    case 2:
			    choice3=1;
			    while(choice3)
			    {
			    	cout<<"������Ϸ"<<endl;
			    	cout<<"1. ��ͨ����   2. �ٷֺ�����"<<endl;
			    	cout<<"0. ����"<<endl;
			    	cin>>choice3;
			    	switch(choice3)
			    	{
			    		case 1:
			    			system("cls");
			    			StartSudokuGenerate(sudoku,NormalBoard);
			    			empty=generateGameBoard(NormalBoard, GameBoard);
			    			GamePlayBoard = GameBoard;	
			    			choice4=1;
			    			while(choice4)
			    			{
			    				bool res;
			    				system("cls");
			    				cout<<"��ͨ����"<<endl;
			    				cout<<"\t1. ��д����    2. �鿴��"<<endl;
			    				cout<<"\t3. ���¿�ʼ    4. ����"<<endl;
			    				cout<<"\t5. DPLL���    0. ����"<<endl;
			    				PrintBoard(GamePlayBoard);
			    				cin >> choice4;
			    				switch(choice4)
			    				{
			    					case 1:
			    						cout << "���������꣨x,y�������֣�"<<endl;
			    						cin >> x >> y >> num;
			    						if(x<1 || x>9 || y<1 || y>9 || num<0 ||num>9)
			    						{
			    							cout<<"�����������������!"<<endl;
			    							system("pause");
			    							break;
										}
										if(GameBoard[(x-1)*9+y-1]!=0)
										{
											cout<<"��λ�ò�����д������������!"<<endl;
											system("pause");
											break;
										}
										//��⵱ǰ�����Ƿ�Ϸ�
										if(CheckBoard(GamePlayBoard,x,y,num)==false)
										{
											cout<<"�����������������!" <<endl;
											system("pause");
											break;
										 } 
										GamePlayBoard[(x-1)*9+y-1]=num;
										cout<<endl;
										PrintBoard(GamePlayBoard);
										break;
									case 2:
										cout<<endl;
										PrintBoard(NormalBoard);
										system("pause");
										break;
									case 3:
										GamePlayBoard=GameBoard;
										system("cls");
										PrintBoard(GamePlayBoard);
										break;
									case 4:
										system("cls");
										break;
									case 5:
										SudokuToCnf(GamePlayBoard,empty);
										if(CNFParser::parse(cnf,"sudoku/NormalSudoku.cnf",numVars,numClauses))
										{
											isread=1;
											numVars=999;
											if(assignments != nullptr) delete[] assignments;
											assignments=new int[numVars+1];
											cout<<"��ȡ�ɹ�"<<endl;
										}
										start_clock = clock();
										res=DPLL(cnf,2,assignments);
										end_clock = clock();
										time_ms=(double)(end_clock - start_clock) * 1000.0 / CLOCKS_PER_SEC;
										printf("ִ��ʱ��Ϊ%.2f ms\n", time_ms);
										if(res)
										{
											 
											
											
											print(assignments,0);
											saveResultToFile("sudoku/NormalSudoku.cnf", res, assignments, time_ms);
										}
										else cout<<"���ɽ�"<<endl;
										system("pause");
										break;
									case 0:
										empty=0;//w
										
										system("cls");
										
										break;
									default:
										break;
								}
			    		
			    				
							}//w
							system("pause");
							break;
							
						case 2:
							system("cls");
							generatePercentSudoku(NormalBoard);
							empty=generateGameBoard(NormalBoard,GameBoard);
							GamePlayBoard=GameBoard;
							
							choice4=1;
							while(choice4)
							{
								bool res;
								system("cls");
			    				cout<<"�ٷֺ�����"<<endl;
			    				cout<<"\t1. ��д����    2. �鿴��"<<endl;
			    				cout<<"\t3. ���¿�ʼ    4. ����"<<endl;
			    				cout<<"\t5. DPLL���    0. ����"<<endl;
			    				PrintBoard(GamePlayBoard);
			    				cin >> choice4;
			    				switch(choice4)
			    				{
			    					case 1:
			    						cout << "���������꣨x,y�������֣�"<<endl;
			    						cin >> x >> y >> num;
			    						if(x<1 || x>9 || y<1 || y>9 || num<0 ||num>9)
			    						{
			    							cout<<"�����������������!"<<endl;
			    							system("pause");
			    							break;
										}
										if(GameBoard[(x-1)*9+y-1]!=0)
										{
											cout<<"��λ�ò�����д������������!"<<endl;
											system("pause");
											break;
										}
										//��⵱ǰ�����Ƿ�Ϸ�
										if(CheckBoard(GamePlayBoard,x,y,num)==false)
										{
											cout<<"�����������������!" <<endl;
											system("pause");
											break;
										 } 
										GamePlayBoard[(x-1)*9+y-1]=num;
										cout<<endl;
										PrintBoard(GamePlayBoard);
										break;
									case 2:
										cout<<endl;
										PrintBoard(NormalBoard);
										system("pause");
										break;
									case 3:
										GamePlayBoard=GameBoard;
										system("cls");
										PrintBoard(GamePlayBoard);
										break;
									case 4:
										system("cls");
										break;
									case 5:
										PercentSudokuToCnf(GamePlayBoard,empty);
										if(CNFParser::parse(cnf,"sudoku/PercentSudoku.cnf",numVars,numClauses))
										{
											isread=1;
											numVars=999;
											if(assignments != nullptr) delete[] assignments;
											assignments=new int[numVars+1];
											cout<<"��ȡ�ɹ�"<<endl;
										}
										start_clock = clock();
										res=DPLL(cnf,2,assignments);
										end_clock = clock();
										time_ms=(double)(end_clock - start_clock) * 1000.0 / CLOCKS_PER_SEC;
										printf("ִ��ʱ��Ϊ%.2f ms\n", time_ms);
										if(res)
										{
											print(assignments,0);
											saveResultToFile("sudoku/PercentSudoku.cnf", res, assignments, time_ms);
										}
										else cout<<"���ɽ�"<<endl;
										system("pause");
										break;
									case 0:
										empty=0;//s
										system("cls");
										break;
									default:
										break;
								}
							}
							system("pause");
						    break;
						case 0:
						    system("cls");
							break;
						default:
						    break;	
					}
				
				}
				break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		    case 0:
		    	cout<<"�˳�����"<<endl;
		    	return 0; 
	    	default:
		    	cout << "������Ч��������" << endl;
		    	
    	}
    
	}
	return 0;
}
	
	    
