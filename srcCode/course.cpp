#include<iostream>

using namespace std;
struct Course {
    char course_name[20];
    int credits;
    char conditions[10000];
    int grade;
};

int main(){
    char temp;
    bool con;
    con=true;
    struct Course type1[100];
    int index;
    index=0;//读到的计数下标
    int count,t;
    count=0;//读到的行数
    int inEnd=true;
    int totalGot,totalTried,totalHave,totalScore;
    totalGot=0;
    totalTried=0;
    totalHave=0;
    totalScore=0;

    while(inEnd){
        //读name
        con=true;
        scanf("%c",&temp);
        if(temp!='\n'){
            while(con){
                if(temp=='|'){
                    index=0;
                    con=false;
                }
                else{
                    type1[count].course_name[index]=temp;//这个地方前端还要改
                    index=index+1;
                    scanf("%c",&temp);
                }
            }
            //读学分
            int credit;
            cin>>credit;
            totalHave=totalHave+credit;
            //判断条件，是否有前置课程
            scanf("%c",&temp);//读'|'
            con=true;
            index=0;
            int length;
            length=0;
            while(con){
                scanf("%c",&temp);
                if(temp=='|'){
                    length=index;
                    con=false;
                }
                else{
                    type1[count].conditions[index]=temp;
                    index=index+1;
                }
            }
            //读
            scanf("%c",&temp);
            if(temp=='\n'||temp=='\r'){
                type1[count].grade=-1;
                count=count+1;
            }
            else{
                if(temp=='A'){
                    t=4;
                    totalScore=totalScore+4*credit;
                    totalTried=totalTried+credit;
                    totalGot=totalGot+credit;
                }
                else if(temp=='B'){
                    t=3;
                    totalScore=totalScore+3*credit;
                    totalTried=totalTried+credit;
                    totalGot=totalGot+credit;
                }
                else if(temp=='C'){
                    t=2;
                    totalScore=totalScore+2*credit;
                    totalTried=totalTried+credit;
                    totalGot=totalGot+credit;
                }
                else if(temp=='D'){
                    t=1;
                    totalScore=totalScore+1*credit;
                    totalTried=totalTried+credit;
                    totalGot=totalGot+credit;
                }
                else if(temp=='F'){
                    t=0;
                    totalTried=totalTried+credit;
                }
                type1[count].grade=t;
                scanf("%c",&temp);//读掉换行符
                count=count+1;
            }
        }
        else{
            inEnd=false;
            //退出循环
        }
    }
    //第一部分输出：
    int totalRemain;
    totalRemain=totalHave-totalGot;
    double res1;
    if(totalGot!=0){
        res1=1.0*totalScore/totalGot;
    }
    else{
        res1=0;
    }
    cout<<"GPA:"<<res1<<endl;
    cout<<"Hours Attempted:"<<totalTried<<endl;
    cout<<"Hours Completed:"<<totalGot<<endl;
    cout<<"credits Remaining:"<<totalRemain<<endl;

    // //遍历推荐
    // int i,j,k;
    // for(i=0;i<count;i=i+1){

    // }
    
}