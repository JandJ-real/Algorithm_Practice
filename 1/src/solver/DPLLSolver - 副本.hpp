#pragma once
//����
//����ѡȡ
//�����ļ�
//��ӡ���
#include"../parser/parser.hpp"
extern int numVars;
//����
//���ݸ������ֽ��д������������ɹ�����true��ʧ�ܷ���false
/*�����µ�cnf��
��ԭcnf����������ɾȥ���к���l��clause���������Ӿ京l��continue��
�����к���l���Ӿ���ɾȥ��l����ɾȥ��l���Ӿ�Ϊ���򷵻�false
Ȼ���ʣ�µ�һ��ŵ���cnf��
��l��¼��assignment������
*/
bool propagate(CNF& cnf, const Literal& l,int* assignments)
{
    CNF newcnf;

    for(size_t i=0;i<cnf.Clauses.size();++i)
    {
        /*Ҫȡ��һ���Ӿ䣬������������Ҫֱ�����ã�*/
        //Clause newclause=cnf.Clauses[i];
        /*���ֳ������ã�ֱ������ԭ���󣬲�*/
        const Clause& clause=cnf.Clauses[i];


        int mark=0;//Ĭ��δ�ҵ�
        for(size_t j=0;j<clause.literals.size();j++)
        {
            if(clause.literals[j]==l)//�ҵ� Ҫֱ���ж�������ȣ������� var==var
            {
                mark=1;
                break;
            }
        }
        if(mark==1) continue;//��������
        else//����ɾ��-l
        {
            Literal negL(-l.var);
            Clause newclause=clause;
            newclause.removeLiteral(negL);
            //ɾ����Ϊ���Ӿ� ����false
            if(newclause.literals.empty())
            {
                return false;
            }
            else
            {
                newcnf.addClause(newclause);
                
            }
            //ѹ����cnf��Ȼ���¼��������
        }
    }
    assignments[abs(l.var)]=(l.var>0)?1:-1;
    cnf=newcnf;
    return true;
}


//ѡȡ���ֲ���:�������� ѡ���һ���Ӿ�ĵ�һ������
Literal selectLiteral_default(CNF& cnf)
{
    if(!cnf.Clauses.empty() && !cnf.Clauses[0].literals.empty()) 
    {
    	return cnf.Clauses[0].literals[0];
	}
    //cerr<<"Non-empty clause not exist"<<endl;
    return Literal(0); 
}


//ѡȡ���ֲ��ԣ�ѡ���������һ������ ���������� Ĭ��Ϊ�� 
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
 
 // ѡ������������� 
Literal selectLiteral_max_new(CNF& cnf)
{
	 
	 int* cnt=new int[numVars * 2 + 1]();

         // ����ÿ����Ԫ�ĳ��ִ���
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

         // ѡ����ִ������ı�Ԫ�����棩
         int maxBool = 0;
         int maxTimes = 0;
         for (int i = 1; i <= numVars; ++i) {
             if (cnt[i] > maxTimes) {
                 maxTimes = cnt[i];
                 maxBool = i;
             }
         }

         // ��������Ԫ�ĳ��ִ������� 1����ѡ�����Ԫ
         if (maxTimes == 1) {
             for (int i = numVars + 1; i <= numVars * 2; ++i) {
                 if (cnt[i] > maxTimes) {
                     maxTimes = cnt[i];
                     maxBool = -(i - numVars);
                 }
             }
         }
         delete[] cnt;
         //ȷ�����ٷ���һ����Ч������
		 if(maxBool==0)
		 {
		 	cout << "δ�ҵ������˵�Ĭ�ϲ���" << endl;
		 	return selectLiteral_default(cnf);
		  } 
         return Literal(maxBool);
 } 

//jw���� 
Literal selectLiteral_jw(CNF& cnf)
{
    MyVector<double> weight(numVars * 2 + 1, 0.0);

         // ����ÿ����Ԫ��Ȩ��
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

         // �ҵ����Ȩ�صı�Ԫ
         double maxWeight = 0.0;
         int maxBool = 0;
         for (int i = 1; i <= numVars; ++i) {
             double totalWeight = weight[i] + weight[i + numVars];
             if (totalWeight > maxWeight) {
                 maxWeight = totalWeight;
                 maxBool = i;
             }
         }

         // ȷ�����ձ�Ԫ�����滹�Ƿ���
         if (weight[maxBool] < weight[maxBool + numVars]) {
             maxBool = -maxBool;
         }

         return Literal(maxBool);
}



bool DPLL(CNF& cnf,int way,int* assignments)
{
    CNF tempcnf=cnf;//��������
    
    while(tempcnf.containsUnitClause())//��һֱ���ڵ��Ӿ�ʱ
    {
        //�Ȼ�ȡ���Ӿ�and���е�����
        Clause unit=tempcnf.getUnitClause_default();
        Literal selectedLiteral=unit.literals[0];
        //�ҵ����Ӿ��Ҵ����ɹ�,����
        //������ʧ�ܣ��򷵻�false
        if(!propagate(tempcnf,selectedLiteral,assignments))
        {
            return false;
        }

        //���CNFΪ�գ�˵�������Ӿ䶼���㣬����true
        if(tempcnf.empty()) return true;
    }
    //�����ڵ��Ӿ䣬�Զ�����ѭ��,ѡ��һ�����ֽ�������
    //Ĭ�ϲ���
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
        if(selectedL.var==0) return false;//û�п�ѡ������

        //�ݹ����DPLL
        //����Ϊ��
        CNF truecnf=tempcnf;

        //����ԭʼֵ�����ڻ���
        int var=abs(selectedL.var);
        int oldVal=assignments[var];


        Literal trueL(abs(selectedL.var));
        //����
        if(propagate(truecnf,trueL,assignments))
        {
            if(DPLL(truecnf,way,assignments))
            {
                return true;
            }
        }
        assignments[var]=oldVal;//����

        
        
        //����Ϊ��
        CNF falsecnf=tempcnf;
        //����ԭʼֵ
        oldVal=assignments[var];
        Literal falseL(-abs(selectedL.var));
        //����
        if(propagate(falsecnf,falseL,assignments))
        {
            
            if(DPLL(falsecnf,way,assignments))
            {
                return true;
            }
        }
        assignments[var]=oldVal;//����
    
    //���ֶ�û��
    return false;
}

void print(int* assignments,int numVars)
{
    
        std::cout << "�н�" << endl;
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
            //�ո�
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
         cerr << "���ļ�: " << filename << "ʧ��" << endl;
         return;
     }

     // д�������
     outFile << "s " << (result ? "1" : "0") << std::endl;

     // д�������ֵ
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
     // д��ִ��ʱ��
     outFile << "t " << duration << std::endl;

     outFile.close();
 }
