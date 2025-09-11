#include"containers/MyVector.hpp"

#include "parser/parser.hpp"

#include"solver/DPLLSolver.hpp"

#include"definition.h"

#include"core/Literal.hpp"//文字
#include"core/Clause.hpp"//子句(文字之或)
#include"core/CNF.hpp"//子句之和

#include"sudoku/GeneratePercentSudoku.hpp"
#include"sudoku/CheckSudokuBoard.hpp"
#include<iostream>
bool SudokuToCnf(const MyVector<int>& board,int empty);
bool PercentSudokuToCnf(const MyVector<int>& board, int empty);//将对角线数独转化为CNF

using namespace std;
// 全局 VSIDS 相关变量
MyVector<double> vsids_score;     // 变量得分表，索引 1 ~ numVars 对应变量 1 ~ numVars
int vsids_decay_counter = 0;      // 用于控制衰减频率
const int VSIDS_DECAY_EVERY = 10; // 每 10 次调用 VSIDS 时衰减一次（可调整）
const double VSIDS_DECAY_FACTOR = 0.5; // 衰减系数，比如 0.5 表示得分减半


int Count=0;
int numVars=0;
int numClauses=0;
int isread=0;
clock_t start_clock;//起始时钟数
clock_t end_clock;//结束时钟数
double time_ms=0;//运行时间 
double time_ms_o=0;//作为比较的初始运行时间 
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
	
	srand(static_cast<unsigned int>(time(nullptr)));//随机数种子
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
		    		
		    		cout << "SAT求解"<<endl;
		    		cout << "1. 读取CNF文件  2.打印CNF文件"<<endl;
		    		cout << "3. 求解CNF文件"<<endl;
			    	cout << "0. 返回"<<endl;
				
			    	cin >> choice2;
				
			    	switch(choice2)
			    	{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				    	case 1:
				    		isread=0;
				    		cout << "输入文件路径" << endl;
				    		cin >> filename;
						
				    		if(CNFParser::parse(cnf,filename,numVars,numClauses))
				    		{
				    			cout << "读取成功" << endl;
				    			isread=1;
				    			//初始化答案数组
				    			vsids_score = MyVector<double>(numVars + 1, 0.0);  // 1-based indexing
				    			if(assignments!=nullptr) delete[] assignments;
				    			assignments = new int[numVars+1]; 
				    		}
				    		time_ms_o=0;
				    		//按任意键继续 
				    		system("pause");
				    		system("cls");
					    	break;
						
				    	case 2:
				    		if(!isread)
					    	{
					    		cout << "文件未读取,请读取后重试" << endl;
							
					    	}
					    	else if(cnf.empty()) cout << "CNF为空" << endl;
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
					    		cout << "请选择分支变元选取策略"<<endl;
					    		cout << "1. 选择首个变元" << endl;
					    		cout << "2. 选择出现最多的变元1"<<endl;
					    		cout << "3. 选择出现最多的变元2"<<endl;
					    		cout << "4. 按jw策略选择权重最高的变元"<<endl; 
					    	
					    		cout << "0. 返回"<<endl; 
					    		cin >> way; 
					    		//记录DPLL执行前的起始时钟数 
					    		start_clock = clock();
					    		
					    		bool res=DPLL(cnf,way,assignments);
					    		//记录执行后的结束时钟数 
					    		end_clock = clock(); 
					    		//计算运行时间
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
									    	cout<<"可解!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "不可解!" << endl;
								    	printf("执行时间为%.2f ms\n", time_ms_o);
										saveResultToFile(filename, res, assignments, time_ms_o); 
								    	system("pause");
								    	system("cls");
								    	break;
								     
								    case 2:
								    	if(res)
								    	{
									    	cout<<"可解!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "不可解!" << endl;
								    	printf("执行时间为%.2f ms\n", time_ms);
								    	if(time_ms_o!=0)
								    	{
								    	    cout << "时间优化率为" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
								    	saveResultToFile(filename, res, assignments, time_ms); 
										 
								    	system("pause");
								    	system("cls");
								    	break;
								    case 3:
								    	if(res)
								    	{
									    	cout<<"可解!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "不可解!" << endl;
								    	printf("执行时间为%.2f ms\n", time_ms);
										if(time_ms_o!=0)
								    	{
								    	    cout << "时间优化率为" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
										saveResultToFile(filename, res, assignments, time_ms);
								    	system("pause");
								    	system("cls");
								    	break;
									case 4:
								    	if(res)
								    	{
									    	cout<<"可解!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "不可解!" << endl;
								    	printf("执行时间为%.2f ms\n", time_ms);
										if(time_ms_o!=0)
								    	{
								    	    cout << "时间优化率为" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
										saveResultToFile(filename, res, assignments, time_ms);
								    	system("pause");
								    	system("cls");
								    	break;	
									case 5:
								    	if(res)
								    	{
									    	cout<<"可解!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "不可解!" << endl;
								    	printf("执行时间为%.2f ms\n", time_ms);
										if(time_ms_o!=0)
								    	{
								    	    cout << "时间优化率为" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
										}
										saveResultToFile(filename, res, assignments, time_ms);
								    	system("pause");
								    	system("cls");
								    	break;	
									case 6:
								    	if(res)
								    	{
									    	cout<<"可解!"<<endl;
									    	print(assignments,numVars) ;
								    	}
								    	else cout << "不可解!" << endl;
								    	printf("执行时间为%.2f ms\n", time_ms);
										if(time_ms_o!=0)
								    	{
								    	    cout << "时间优化率为" << (time_ms_o - time_ms) / time_ms_o * 100 << "%" << endl;	
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
					    		cout << "文件未读取,请读取后重试" << endl;
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
			    	cout<<"数独游戏"<<endl;
			    	cout<<"1. 普通数独   2. 百分号数独"<<endl;
			    	cout<<"0. 返回"<<endl;
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
			    				cout<<"普通数独"<<endl;
			    				cout<<"\t1. 填写数字    2. 查看答案"<<endl;
			    				cout<<"\t3. 重新开始    4. 清屏"<<endl;
			    				cout<<"\t5. DPLL求解    0. 返回"<<endl;
			    				PrintBoard(GamePlayBoard);
			    				cin >> choice4;
			    				switch(choice4)
			    				{
			    					case 1:
			    						cout << "请输入坐标（x,y）和数字："<<endl;
			    						cin >> x >> y >> num;
			    						if(x<1 || x>9 || y<1 || y>9 || num<0 ||num>9)
			    						{
			    							cout<<"输入错误，请重新输入!"<<endl;
			    							system("pause");
			    							break;
										}
										if(GameBoard[(x-1)*9+y-1]!=0)
										{
											cout<<"该位置不可填写，请重新输入!"<<endl;
											system("pause");
											break;
										}
										//检测当前局面是否合法
										if(CheckBoard(GamePlayBoard,x,y,num)==false)
										{
											cout<<"输入错误，请重新输入!" <<endl;
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
											cout<<"读取成功"<<endl;
										}
										start_clock = clock();
										res=DPLL(cnf,2,assignments);
										end_clock = clock();
										time_ms=(double)(end_clock - start_clock) * 1000.0 / CLOCKS_PER_SEC;
										printf("执行时间为%.2f ms\n", time_ms);
										if(res)
										{
											 
											
											
											print(assignments,0);
											saveResultToFile("sudoku/NormalSudoku.cnf", res, assignments, time_ms);
										}
										else cout<<"不可解"<<endl;
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
			    				cout<<"百分号数独"<<endl;
			    				cout<<"\t1. 填写数字    2. 查看答案"<<endl;
			    				cout<<"\t3. 重新开始    4. 清屏"<<endl;
			    				cout<<"\t5. DPLL求解    0. 返回"<<endl;
			    				PrintBoard(GamePlayBoard);
			    				cin >> choice4;
			    				switch(choice4)
			    				{
			    					case 1:
			    						cout << "请输入坐标（x,y）和数字："<<endl;
			    						cin >> x >> y >> num;
			    						if(x<1 || x>9 || y<1 || y>9 || num<0 ||num>9)
			    						{
			    							cout<<"输入错误，请重新输入!"<<endl;
			    							system("pause");
			    							break;
										}
										if(GameBoard[(x-1)*9+y-1]!=0)
										{
											cout<<"该位置不可填写，请重新输入!"<<endl;
											system("pause");
											break;
										}
										//检测当前局面是否合法
										if(CheckBoard(GamePlayBoard,x,y,num)==false)
										{
											cout<<"输入错误，请重新输入!" <<endl;
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
											cout<<"读取成功"<<endl;
										}
										start_clock = clock();
										res=DPLL(cnf,2,assignments);
										end_clock = clock();
										time_ms=(double)(end_clock - start_clock) * 1000.0 / CLOCKS_PER_SEC;
										printf("执行时间为%.2f ms\n", time_ms);
										if(res)
										{
											print(assignments,0);
											saveResultToFile("sudoku/PercentSudoku.cnf", res, assignments, time_ms);
										}
										else cout<<"不可解"<<endl;
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
		    	cout<<"退出程序"<<endl;
		    	return 0; 
	    	default:
		    	cout << "操作无效，请重试" << endl;
		    	
    	}
    
	}
	return 0;
}
	
	    
