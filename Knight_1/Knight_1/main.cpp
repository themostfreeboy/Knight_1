/*
此程序采用按顺序选择每步的方向，出错则回溯，所以导致试探中回溯次数过多，时间过长，效率极低。
*/

#include <stdio.h>
#include <stdlib.h>

#define num 100

class mydata
{
public:
	int x;//横坐标
	int y;//纵坐标
	int k;//下一步的方向(即dx和dy数组的数组下标)
	mydata(){};
	mydata(int x,int y,int k):x(x),y(y),k(k){};
};

class stack
{
public:
	mydata data[num];
	int top;
	void push(mydata x);//入栈
	mydata pop();//出栈
	bool Full();//栈满
	bool Empty();//栈空
	stack():top(-1){};
	void copy(stack *s);//栈内内容复制
};

void stack::push(mydata x)//入栈
{
	if(top<num-1)    data[++top]=x;
}

mydata stack::pop()//出栈
{
	if(top>-1)    return data[top--];
}

bool stack::Full()//栈满
{
	return (top==num-1)?true:false;
}

bool stack::Empty()//栈空
{
	return (top==-1)?true:false;
}

void stack::copy(stack *s)//栈内内容复制
{
	for(int i=0;i<=s->top;i++)
	{
		push(s->data[i]);
	}
}

int main()
{
	const int dx[8]={1,1,-1,-1,2,2,-2,-2};
	const int dy[8]={2,-2,2,-2,1,-1,1,-1};
	int position_x=0;//初始横坐标
	int position_y=0;//初始纵坐标
	int data[8][8];//用于记录某点是否已经走过或者走过的顺序
	bool result=false;//用于记录是否能够完成遍历
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			data[i][j]=0;
	data[position_x][position_y]=1;
	int i=0;//横坐标
	int j=0;//纵坐标
	int k=0;//每一步的走法(对应于dx和dy的数组下标)
	int step=0;//用于记录步数
	stack *s=new stack;
    i=position_x;
	j=position_y;
	step++;
	data[i][j]=step;
	while(true)
	{
		if(k>=8)//当8种方法都试了仍无满足要求的方法，则弹栈
		{
			if(s->Empty())//如果栈为空，则说明所有方法已枚举完毕，无法完成遍历，退出最外层循环即可
			{
				result=false;
				break;
			}
			mydata md=s->pop();
			i=md.x;
			j=md.y;
			k=md.k;
			data[i+dx[k]][j+dy[k]]=0;
			step--;
			k++;
			continue;
		}
		if(i+dx[k]>=0 && i+dx[k]<8 && j+dy[k]>=0 && j+dy[k]<8 && data[i+dx[k]][j+dy[k]]==0)//下一步未超过棋盘界限
		{
			mydata md(i,j,k);
		    s->push(md);
			i=i+dx[k];
			j=j+dy[k];
			step++;
			data[i][j]=step;
			k=0;//下一步的方法k从0开始扫描
		}
		else if(step==64)//当前k不满足要求，但是已完成遍历(当此处设置step的值为61或以下时，速度可以，当设置为62,63,64时，时间过长，回溯次数过多，效率极低)
		{
			result=true;
			break;
		}
		else//当前k不满足要求，但是未完成遍历
		{
			k++;//继续扫描下一个k
		}
	}
	delete s;
	if(result==true)
	{
	    for(i=0;i<8;i++)
	    {
		    for(j=0;j<8;j++)
			{
				printf("%d\t",data[i][j]);
			}
		    printf("\n");
	    }
	}
	else if(result==false)
	{
		printf("无法完成遍历\n");
	}
	system("pause");
	return 0;
}