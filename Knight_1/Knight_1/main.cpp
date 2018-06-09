/*
�˳�����ð�˳��ѡ��ÿ���ķ��򣬳�������ݣ����Ե�����̽�л��ݴ������࣬ʱ�������Ч�ʼ��͡�
*/

#include <stdio.h>
#include <stdlib.h>

#define num 100

class mydata
{
public:
	int x;//������
	int y;//������
	int k;//��һ���ķ���(��dx��dy����������±�)
	mydata(){};
	mydata(int x,int y,int k):x(x),y(y),k(k){};
};

class stack
{
public:
	mydata data[num];
	int top;
	void push(mydata x);//��ջ
	mydata pop();//��ջ
	bool Full();//ջ��
	bool Empty();//ջ��
	stack():top(-1){};
	void copy(stack *s);//ջ�����ݸ���
};

void stack::push(mydata x)//��ջ
{
	if(top<num-1)    data[++top]=x;
}

mydata stack::pop()//��ջ
{
	if(top>-1)    return data[top--];
}

bool stack::Full()//ջ��
{
	return (top==num-1)?true:false;
}

bool stack::Empty()//ջ��
{
	return (top==-1)?true:false;
}

void stack::copy(stack *s)//ջ�����ݸ���
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
	int position_x=0;//��ʼ������
	int position_y=0;//��ʼ������
	int data[8][8];//���ڼ�¼ĳ���Ƿ��Ѿ��߹������߹���˳��
	bool result=false;//���ڼ�¼�Ƿ��ܹ���ɱ���
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			data[i][j]=0;
	data[position_x][position_y]=1;
	int i=0;//������
	int j=0;//������
	int k=0;//ÿһ�����߷�(��Ӧ��dx��dy�������±�)
	int step=0;//���ڼ�¼����
	stack *s=new stack;
    i=position_x;
	j=position_y;
	step++;
	data[i][j]=step;
	while(true)
	{
		if(k>=8)//��8�ַ�����������������Ҫ��ķ�������ջ
		{
			if(s->Empty())//���ջΪ�գ���˵�����з�����ö����ϣ��޷���ɱ������˳������ѭ������
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
		if(i+dx[k]>=0 && i+dx[k]<8 && j+dy[k]>=0 && j+dy[k]<8 && data[i+dx[k]][j+dy[k]]==0)//��һ��δ�������̽���
		{
			mydata md(i,j,k);
		    s->push(md);
			i=i+dx[k];
			j=j+dy[k];
			step++;
			data[i][j]=step;
			k=0;//��һ���ķ���k��0��ʼɨ��
		}
		else if(step==64)//��ǰk������Ҫ�󣬵�������ɱ���(���˴�����step��ֵΪ61������ʱ���ٶȿ��ԣ�������Ϊ62,63,64ʱ��ʱ����������ݴ������࣬Ч�ʼ���)
		{
			result=true;
			break;
		}
		else//��ǰk������Ҫ�󣬵���δ��ɱ���
		{
			k++;//����ɨ����һ��k
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
		printf("�޷���ɱ���\n");
	}
	system("pause");
	return 0;
}