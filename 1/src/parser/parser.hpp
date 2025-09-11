#pragma once

#include "../core/CNF.hpp"
class CNFParser
{
    public:

        //静态方法，无需创建对象示例即可调用
        static bool parse(CNF& cnf, const string& filename, int&NumVars,int& NumClauses)
        {
            ifstream file(filename);//不是"filename"! 引用
            std::string line;//要加上std::

            //打开文件失败
            if(!file.is_open())
            {
                cerr << "打开文件" << filename << "失败" << endl;
                return false;

            }/*else
            {
                cerr << "打开文件" << filename << "成功" << endl;
            }*/
            

            //若CNF非空，清空CNF
            //若CNF中已有数据，直接添加新数据会导致旧数据残留
            /*确保数据纯净，每次解析都从空的CNF开始，避免上次解析结果污染
            且允许同一个CNF对象被多次用于解析不同文件*/
            if(!cnf.empty())
            {
                cnf.Clauses.clear();
            }
            while(getline(file,line))
            {
                istringstream iss(line);//将字符串line转换为输入流

                if(line.empty() || line[0]=='c') continue;
                if(line[0] == 'p')
                {
                    string p_str,cnf_str;
                    if(!(iss >> p_str >> cnf_str >> NumVars >> NumClauses))
                    {
                        cerr << "公式格式错误" << endl;
                        return false;
                    }
                    if(p_str!="p" || cnf_str!="cnf")
                    {
                        cerr << "文件头标识符错误" << endl;
                        return false;
                    }
                    /*
                    if (NumVars <= 0 || NumClauses <= 0) {
                        cerr << "无效的变量数或子句数!" << endl;
                        return false;
                    }*/
                }
                else
                {
                    Clause clause;
                    int var;
                    while(iss >> var && var!=0)
                    {
                        //Literal l=Literal(var);
                        clause.addLiteral(Literal(var));
                    }
                    cnf.addClause(clause);
                }
                
            }
            file.close();//记得关闭文件！！
            return true;
        }
};
