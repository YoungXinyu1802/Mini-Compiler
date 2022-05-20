
void kuaipai(int a[],int start,int end)    //start和end都是指下标
{
    int i,j,temp,x;
    i=start;
    j=end;
    x=a[start];    //选取基准值
    while(i<j)
    {
        while(i<j && x<a[j])    //从右向左搜索小于基准值的数,让j等于它的下标
            j--;
        while(i<j && x>a[i])    //从左向右搜索大于基准值的数,让i等于它的下标
            i++;
        if(i<j)    //在满足i<j的条件下，交换a[i]和a[j]的值 
        {
            temp=a[j];
            a[j]=a[i];
            a[i]=temp;
        }
    }
    temp=x;   //跳出循环之后，把基准值和a[i]调换 
    x=a[i];
    a[i]=temp;
    if(start<j)    //递归 
        kuaipai(a,start,j-1);
	if(i<end)
        kuaipai(a,j+1,end);
}
void print(int s[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",s[i]);
    printf("\n");
}
 
int main()
{
    int a[]={6,1,2,8,4,9,5,3};
	print(a,8);    //先在屏幕上输出原来的数字序列 
	kuaipai(a,0,7);    //调用快排函数，将a排序 
	print(a,8);    //输出排好序的数字序列 
}