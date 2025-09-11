#pragma once

#include "../core/CNF.hpp"
class CNFParser
{
    public:

        //��̬���������贴������ʾ�����ɵ���
        static bool parse(CNF& cnf, const string& filename, int&NumVars,int& NumClauses)
        {
            ifstream file(filename);//����"filename"! ����
            std::string line;//Ҫ����std::

            //���ļ�ʧ��
            if(!file.is_open())
            {
                cerr << "���ļ�" << filename << "ʧ��" << endl;
                return false;

            }/*else
            {
                cerr << "���ļ�" << filename << "�ɹ�" << endl;
            }*/
            

            //��CNF�ǿգ����CNF
            //��CNF���������ݣ�ֱ����������ݻᵼ�¾����ݲ���
            /*ȷ�����ݴ�����ÿ�ν������ӿյ�CNF��ʼ�������ϴν��������Ⱦ
            ������ͬһ��CNF���󱻶�����ڽ�����ͬ�ļ�*/
            if(!cnf.empty())
            {
                cnf.Clauses.clear();
            }
            while(getline(file,line))
            {
                istringstream iss(line);//���ַ���lineת��Ϊ������

                if(line.empty() || line[0]=='c') continue;
                if(line[0] == 'p')
                {
                    string p_str,cnf_str;
                    if(!(iss >> p_str >> cnf_str >> NumVars >> NumClauses))
                    {
                        cerr << "��ʽ��ʽ����" << endl;
                        return false;
                    }
                    if(p_str!="p" || cnf_str!="cnf")
                    {
                        cerr << "�ļ�ͷ��ʶ������" << endl;
                        return false;
                    }
                    /*
                    if (NumVars <= 0 || NumClauses <= 0) {
                        cerr << "��Ч�ı��������Ӿ���!" << endl;
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
            file.close();//�ǵùر��ļ�����
            return true;
        }
};
