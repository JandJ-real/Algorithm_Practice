#pragma once
//传播
//策略选取
//保存文件
//打印结果
#include"../parser/parser.hpp"
extern int numVars;
//传播
//根据给定文字进行传播，若传播成功返回true，失败返回false
/*创建新的cnf，
在原cnf挨个遍历，删去所有含有l的clause，即若该子句含l则continue，
在所有含非l的子句里删去非l，若删去非l后子句为空则返回false
然后和剩下的一起放到新cnf里
把l记录在assignment数组里
*/
bool propagate(CNF& cnf, const Literal& l,int* assignments)
{
    CNF newcnf;

    for(size_t i=0;i<cnf.Clauses.size();++i)
    {
        /*要取出一个子句，拷贝副本，不要直接引用！*/
        //Clause newclause=cnf.Clauses[i];
        /*这种常量引用，直接引用原对象，不*/
        const Clause& clause=cnf.Clauses[i];


        int mark=0;//默认未找到
        for(size_t j=0;j<clause.literals.size();j++)
        {
            if(clause.literals[j]==l)//找到 要直接判断文字相等，不能是 var==var
            {
                mark=1;
                break;
            }
        }
        if(mark==1) continue;//跳过后面
        else//否则删除-l
        {
            Literal negL(-l.var);
            Clause newclause=clause;
            newclause.removeLiteral(negL);
            //删掉后为空子句 返回false
            if(newclause.literals.empty())
            {
                return false;
            }
            else
            {
                newcnf.addClause(newclause);
                
            }
            //压到新cnf，然后记录在数组内
        }
    }
    assignments[abs(l.var)]=(l.var>0)?1:-1;
    cnf=newcnf;
    return true;
}


//选取文字策略:基础策略 选择第一个子句的第一个文字
Literal selectLiteral_default(CNF& cnf)
{
    if(!cnf.Clauses.empty() && !cnf.Clauses[0].literals.empty()) 
    {
    	return cnf.Clauses[0].literals[0];
	}
    //cerr<<"Non-empty clause not exist"<<endl;
    return Literal(0); 
}


//选取文字策略：选择出现最多的一个文字 不考虑正负 默认为正 
Literal selectLiteral_max(CNF& cnf)
{
	int* arr=new int[numVars+1]();
	/*for(size_t i=0;i<cnf.Clauses.size();++i)
	{
		for(int j=0;j<cnf.Clauses[i].literals.size();++j)
		{
			arr[abs(cnf.Clauses[i].literals[j].var)]++;
		}
	}*/
	for(const Clause& clause : cnf.Clauses)
	{
		for(const Literal& literal : clause.literals)
		{
			arr[abs(literal.var)]++;
		}
	} 
	int max=0;
	for(int i=1;i<=numVars;++i)
	{
		if(arr[i] > arr[max]) max=i;
	}
	delete[] arr;
	return Literal(max);
 } 
 
 // 选择出现最多的文字 
Literal selectLiteral_max_new(CNF& cnf)
{
	 
	 int* cnt=new int[numVars * 2 + 1]();

         // 计算每个变元的出现次数
         //
         for (const Clause& clause : cnf.Clauses) {
             for (const Literal& literal : clause.literals) {
                 if (literal.var > 0) {
                     cnt[literal.var]++;
                 }
                 else {
                     cnt[numVars - literal.var]++;
                 }
             }
         }

         // 选择出现次数最多的变元（正面）
         int maxBool = 0;
         int maxTimes = 0;
         for (int i = 1; i <= numVars; ++i) {
             if (cnt[i] > maxTimes) {
                 maxTimes = cnt[i];
                 maxBool = i;
             }
         }

         // 如果正面变元的出现次数都是 1，则选择反面变元
         if (maxTimes == 1) {
             for (int i = numVars + 1; i <= numVars * 2; ++i) {
                 if (cnt[i] > maxTimes) {
                     maxTimes = cnt[i];
                     maxBool = -(i - numVars);
                 }
             }
         }
         delete[] cnt;
         //确保至少返回一个有效的文字
		 if(maxBool==0)
		 {
		 	cout << "未找到，回退到默认策略" << endl;
		 	return selectLiteral_default(cnf);
		  } 
         return Literal(maxBool);
 } 

//jw策略 
Literal selectLiteral_jw(CNF& cnf)
{
    MyVector<double> weight(numVars * 2 + 1, 0.0);

         // 计算每个变元的权重
         for (const Clause& clause : cnf.Clauses) {
             double clauseWeight = pow(2.0, -static_cast<double>(clause.literals.size()));
             for (const Literal& literal : clause.literals) {
                 int varIndex = std::abs(literal.var);
                 if (literal.var > 0) {
                     weight[varIndex] += clauseWeight;
                 }
                 else {
                     weight[numVars - literal.var] += clauseWeight;
                 }
             }
         }

         // 找到最大权重的变元
         double maxWeight = 0.0;
         int maxBool = 0;
         for (int i = 1; i <= numVars; ++i) {
             double totalWeight = weight[i] + weight[i + numVars];
             if (totalWeight > maxWeight) {
                 maxWeight = totalWeight;
                 maxBool = i;
             }
         }

         // 确定最终变元是正面还是反面
         if (weight[maxBool] < weight[maxBool + numVars]) {
             maxBool = -maxBool;
         }

         return Literal(maxBool);
}



bool DPLL(CNF& cnf,int way,int* assignments)
{
    CNF tempcnf=cnf;//拷贝副本
    
    while(tempcnf.containsUnitClause())//当一直存在单子句时
    {
        //先获取单子句and其中的文字
        Clause unit=tempcnf.getUnitClause_default();
        Literal selectedLiteral=unit.literals[0];
        //找到单子句且传播成功,继续
        //若传播失败，则返回false
        if(!propagate(tempcnf,selectedLiteral,assignments))
        {
            return false;
        }

        //如果CNF为空，说明所有子句都满足，返回true
        if(tempcnf.empty()) return true;
    }
    //不存在单子句，自动跳出循环,选择一个文字进行搜索
    //默认策略
    Literal selectedL(0); 
    if(way==1)
    {
        selectedL=selectLiteral_default(tempcnf);
    }
    else if(way==2)
	{
		selectedL=selectLiteral_max(tempcnf);
	} 
	else if(way==3)
	{
		selectedL=selectLiteral_max_new(tempcnf);
	}
	else if(way==4)
	{
		selectedL=selectLiteral_jw(tempcnf);
	}
        if(selectedL.var==0) return false;//没有可选的文字

        //递归调用DPLL
        //文字为真
        CNF truecnf=tempcnf;

        //保存原始值，便于回溯
        int var=abs(selectedL.var);
        int oldVal=assignments[var];


        Literal trueL(abs(selectedL.var));
        //传播
        if(propagate(truecnf,trueL,assignments))
        {
            if(DPLL(truecnf,way,assignments))
            {
                return true;
            }
        }
        assignments[var]=oldVal;//回溯

        
        
        //文字为假
        CNF falsecnf=tempcnf;
        //保存原始值
        oldVal=assignments[var];
        Literal falseL(-abs(selectedL.var));
        //传播
        if(propagate(falsecnf,falseL,assignments))
        {
            
            if(DPLL(falsecnf,way,assignments))
            {
                return true;
            }
        }
        assignments[var]=oldVal;//回溯
    
    //两种都没有
    return false;
}

void print(int* assignments,int numVars)
{
    
        std::cout << "有解" << endl;
        for(int i=1;i<=numVars;++i)
        {
            if(assignments[i]>0)
            {
                std::cout << i << " ";
            }
            else if(assignments[i]<0)
            {
                std:: cout << -i << " ";
            }
            //空格
            else cout << 0 << " ";
        }
        std::cout << std::endl;
    
}

 void saveResultToFile(const std::string& baseFilename, bool result, const int* assignments,double duration) {
     string filename = baseFilename;
     filename.erase(filename.end() - 4,filename.end());
     filename += ".res";
     ofstream outFile(filename);

     if (!outFile) {
         cerr << "打开文件: " << filename << "失败" << endl;
         return;
     }

     // 写入求解结果
     outFile << "s " << (result ? "1" : "0") << std::endl;

     // 写入变量赋值
     outFile << "v ";
     if (result) {
     for (int i = 1; i <= numVars; ++i) {
         if (assignments[i] == 1) {
             outFile << i << " ";
         }
         else if (assignments[i] == -1) {
             outFile << -i << " ";
         }
     }
     outFile << std::endl;
 }
     // 写入执行时间
     outFile << "t " << duration << std::endl;

     outFile.close();
 }
