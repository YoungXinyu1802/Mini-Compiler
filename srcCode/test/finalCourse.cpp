#include<iostream>

using namespace std;
struct Course {
    char course_name[5];
    int learned;
    int name_size;
    char conditions[10000];
    int length;
};

int HashFunc(char key[], int TableSize,int size){
    int HashVal;
    HashVal= 0;
    int i;
    i=0;
    while(i!=size){
        HashVal = HashVal*32 + key[i];
        i = i+1;
    }
    int quotient;
    quotient = HashVal / TableSize;
    int rem;
    rem = HashVal - quotient*TableSize;
    return rem;
}

int main(){
    char temp;
    bool con;
    con=true;
    int i,j,k,z;
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
    int totalCourse;
    totalCourse=0;
    char test[2];
    char zero=test[1];//测一下

    while(inEnd){
        //读name
        con=true;
        scanf("%c",&temp);
        if(temp!='\n'){
            totalCourse=totalCourse+1;
            index=0;//改
            while(con){
                if(temp=='|'){
                    type1[count].name_size=index;
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
                    type1[count].length=index;
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
                type1[count].learned=-1;
                count=count+1;
            }
            else{
                if(temp=='A'){
                    t=4;
                    totalScore=totalScore+4*credit;
                    totalTried=totalTried+credit;
                    totalGot=totalGot+credit;
                    type1[count].learned=1;
                }
                else if(temp=='B'){
                    t=3;
                    totalScore=totalScore+3*credit;
                    totalTried=totalTried+credit;
                    totalGot=totalGot+credit;
                    type1[count].learned=1;
                }
                else if(temp=='C'){
                    t=2;
                    totalScore=totalScore+2*credit;
                    totalTried=totalTried+credit;
                    totalGot=totalGot+credit;
                    type1[count].learned=1;
                }
                else if(temp=='D'){
                    t=1;
                    totalScore=totalScore+1*credit;
                    totalTried=totalTried+credit;
                    totalGot=totalGot+credit;
                    type1[count].learned=1;
                }
                else if(temp=='F'){
                    t=0;
                    totalTried=totalTried+credit;
                    type1[count].learned=-1;
                }
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
        res1=1.0*totalScore/totalTried;
    }
    else{
        res1=0;
    }
    cout<<"GPA:"<<res1<<endl;
    cout<<"Hours Attempted:"<<totalTried<<endl;
    cout<<"Hours Completed:"<<totalGot<<endl;
    cout<<"credits Remaining:"<<totalRemain<<endl;

    cout<<"Possible Courses to Take Next"<<endl;
    int courseNum;
    courseNum=0;
    // part 2
    int tHash,tableSize,nameSize;
    tHash=0;
    tableSize=1000;
    int myHashTable[1000];
    char tName[5];
    int credited;
    for(i=0;i<totalCourse;i=i+1){
        for(j=0;j<5;j=j+1){//remainto modified
            tName[j]=type1[i].course_name[j];
        }
        nameSize=type1[i].name_size;
        tHash=HashFunc(tName,tableSize,nameSize);
        //
        credited=type1[i].learned;
        if(myHashTable[tHash]==0){
            if(credited==-1){
                myHashTable[tHash]=1;//有但未修读
            }
            else{
                myHashTable[tHash]=2;//有且已修读
            }
        }
        else if(myHashTable[tHash]!=0){
            myHashTable[tHash]=3;//有且Hash冲突
        } 
    }
    //遍历判断修读条件
    int isOk,flag;
    isOk=0;
    for(i=0;i<totalCourse;i=i+1){
        //只有未修读课程才需要处理
        if(type1[i].learned==-1){
            //处理前置条件
            if(type1[i].length==0){
                //无前置条件，可以直接输出
                courseNum=1;
                cout<<type1[i].course_name<<endl;
            }
            else{//需要判断前置条件
                isOk=1;//初始设为true完成条件
                index=0;
                for(j=0;j<type1[i].length;j=j+1){
                    temp=type1[i].conditions[j];
                    if((temp==',')||(temp==';')){
                        //
                        for(z=index;z<5;z=z+1){
                            tName[z]=zero;
                        }
                        tHash=HashFunc(tName,tableSize,index);
                        index=0;
                        if(myHashTable[tHash]==0){
                            if(isOk==1){
                                isOk=0;
                            }
                        }
                        else if(myHashTable[tHash]==1){
                            if(isOk==1){
                                isOk=0;
                            }
                        }
                        else if(myHashTable[tHash]==2){
                            if(isOk==1){
                                isOk=1;
                            }
                        }
                        else{
                            //myHashTable[tHash]==3;
                            for(k=0;k<totalCourse;k=k+1){
                                flag=1;
                                for(z=0;z<5;z=z+1){
                                    if(type1[k].course_name[z]!=tName[z]){
                                        flag=-1;
                                        z=5;
                                    }
                                }
                                if(flag==1){
                                    //remained to modified
                                    if((type1[k].learned==1)&&(isOk==1)){
                                        isOk=1;
                                    }
                                    else{
                                        isOk=-1;
                                    }
                                    k=totalCourse;
                                }
                            }
                        }
                        if(temp==';'){
                            if(isOk==1){
                                j=type1[i].length;//直接完成循环
                            }
                            else{
                                isOk=1;
                            }
                        }
                    }
                    else{
                        tName[index]=temp;
                        index=index+1;
                    }
                }
                //
                //处理末尾条件
                if(temp!=';'){
                    nameSize=index;
                    for(z=index;z<5;z=z+1){
                        tName[z]=zero;
                    }
                    tHash=HashFunc(tName,tableSize,nameSize);
                    if(myHashTable[tHash]==0){
                        if(isOk==1){
                            isOk=0;
                        }
                    }
                    else if(myHashTable[tHash]==1){
                        if(isOk==1){
                            isOk=0;
                        }
                    }
                    else if(myHashTable[tHash]==2){
                        if(isOk==1){
                            isOk=1;
                        }
                    }
                    else{
                        //myHashTable[tHash]==3;
                        for(k=0;k<totalCourse;k=k+1){
                            flag=1;
                            for(z=0;z<5;z=z+1){
                                if(type1[k].course_name[z]!=tName[z]){
                                    flag=-1;
                                    z=5;
                                }
                            }
                            if(flag==1){
                                //remained to modified
                                if((type1[k].learned==1)&&(isOk==1)){
                                    isOk=1;
                                }
                                else{
                                    isOk=-1;
                                }
                                k=totalCourse;
                            }
                        }
                    }
                }
                if(isOk==1){
                    //符合修读条件
                    courseNum=1;
                    cout<<type1[i].course_name<<endl;
                }
            }
        }
    }
    //完成循环
    if(courseNum==0){
        cout<<"  None - Congratulations!"<<endl;
    }

    return 0;
}

