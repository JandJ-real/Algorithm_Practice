#include <iostream>
#include <cstring>
#include<bits/stdc++.h>

using namespace std;
class phone{
       char number[12];
       char city[5];
       double fee;
       public:
       phone(){
              strcpy(number,"08600000000");
              strcpy(city,"***");
              fee=0;
       }
       void recharge(double amount){
              fee+=amount;
       }
       void insertcard(const char*n,const char*c){
              strcpy(number,n);
              strcpy(city,c);
       }
       double getfee() {
              return fee;
       }
       char* getno(){
              return number;
       }
       char* getcity(){
              return city;
       }
       int call(phone &other,int m){
              double per1,per2;
              if(strcmp(city,other.city)==0){
                     per1=0.7;
                     per2=0.0;
              }
              else{
                     per1=1.2;
                     per2=0.7;
              }
              int talktime=m;
              double cost1,cost2;
              double maxtime1=fee/per1;
              double maxtime2=other.fee/per2;
              if(maxtime1<m)
              talktime=(int)maxtime1;
              if(maxtime2<talktime)
              talktime=(int)maxtime2;
              cost1=talktime*per1;
              cost2=talktime*per2;
              fee-=cost1;
              other.fee-=cost2;
              return talktime;
       }
};

void display( phone t)
{      
       cout<<"手机号码："<<t.getno()
              <<"；归属地："<<t.getcity()
              <<"；话费余额："<<t.getfee()
              <<endl;
}

int main()
{
       phone p1;
       display(p1);
       p1.insertcard("13458901211","027");      p1.recharge(40);

       phone p2,p3;
       p2.insertcard("13652901219","021");      p2.recharge(30);  
       p3.insertcard("15651004523","027");      p3.recharge(50);

       int talk,m;
       m=35;
       talk=p1.call(p2,m);
       char *line="*-------------------------------------------------*";
       cout<<line<<endl;
       cout<<"p1主叫p2......."<<endl;
       if (talk==m) 
              cout<<"通话时长"<<talk<<"分钟。通话结束,祝您愉快"<<endl;
       else 
              cout<<"通话时长"<<talk<<"分钟。余额不足,请尽快预存话费"<<endl;
       display(p1); 
       display(p2);
       cout<<line<<endl;
       p1.recharge(30);
       m=40;
       talk=p3.call(p1,40);
       cout<<line<<endl;
       cout<<"p3主叫p1......."<<endl;
       if (talk==m) 
              cout<<"通话时长"<<talk<<"分钟。通话结束,祝您愉快........"<<endl;
       else 
              cout<<"通话时长"<<talk<<"分钟。电话余额不足.......请尽快预存话费."<<endl;;
       display(p3); display(p1);
       cout<<line<<endl;
       return 0;
}