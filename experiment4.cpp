#include<iostream>
#include<cstring>
#include<string>
using namespace std;
#define m 10
struct
{
	float address;     /*起始地址*/
	float length;      /*长度*/
	int flag;          /*标志，用"0"表示空栏目，用"1"表示未分配*/
}free_table[m];      /*空闲区表*/
struct WORK
{
	float address;
	float length;
	string name;
	int block;
}work[m];

int Free_Num=0;
int Work_Num=0;
int Space_Size=0;

void InitSpace()
{
	int init;
	int ending;
	cout<<"*********************************"<<endl;
	cout<<"please enter the initial address:"<<endl;
	cout<<"*********************************"<<endl;
	cin>>init;
	free_table[0].address=init;
	cout<<"********************************"<<endl;
	cout<<"please enter the ending address:"<<endl;
	cout<<"********************************"<<endl;
	cin>>ending;
	free_table[0].flag=1;
	cout<<"Successfully entered……"<<endl;
	cout<<"******************"<<endl;
	cout<<"设置分区每一块大小:"<<endl;
	cout<<"******************"<<endl;
	int total=0;
	for(int i=0;i<m;i++)
	{
		cin>>Space_Size;
        total=total+Space_Size;
		if(i==0)
		{
            if(total==ending-init+1)
            {
                cout<<"full allocation"<<endl;
                free_table[i].address=init;
                free_table[i].length=ending-free_table[i].address+1;
                free_table[i].flag=1;
                Free_Num++;
                break;
            }
			free_table[0].length=Space_Size;
			continue;
		}

		if(total>ending-init+1)
		{
			cout<<"no enough space"<<endl;
			free_table[i].address=free_table[i-1].address+free_table[i-1].length;
			free_table[i].length=ending-free_table[i].address+1;
			free_table[i].flag=1;
			Free_Num++;
			break;
		}

		free_table[i].address=free_table[i-1].address+free_table[i-1].length;
		if(free_table[i].address+free_table[i].length-1<=ending)
			free_table[i].length=Space_Size;
		else
			free_table[i].length=ending-free_table[i].address;
		free_table[i].flag=1;
		Free_Num++;
	}
}

void ShowSpace()
{
	cout<<"TabNum\tLength\tStartAddress\tEndAddress\tStatus"<<endl;
	cout<<"------------------------------------------------------"<<endl;
	for(int i=0;i<m;i++)
	{
		if(free_table[i].length==0)
		{
			cout<<"|Tab"<<i+1<<"|\t"<<free_table[i].length<<"\t"<<"0"<<"\t\t";\
			cout<<"0"<<"\t\t"<<"empty"<<endl;
			continue;
		}
		if(free_table[i].flag==1)
		{
			cout<<"|Tab"<<i+1<<"|\t"<<free_table[i].length<<"\t"<<free_table[i].address<<"\t\t";\
			cout<<free_table[i].address+free_table[i].length-1<<"\t\t"<<"unallocated"<<endl;

		}
		else if(free_table[i].flag==0)
		{
			cout<<"|Tab"<<i+1<<"|\t"<<free_table[i].length<<"\t"<<free_table[i].address<<"\t\t";\
			cout<<free_table[i].address+free_table[i].length-1<<"\t\t"<<"empty"<<endl;
		}

	}
	cout<<"The number of free space is :"<<Free_Num<<endl;
}

void AllocateSpace()
{
	cout<<"******************************"<<endl;
	cout<<"please enter the needed space:"<<endl;
	cout<<"******************************"<<endl;
	cin>>work[Work_Num].length;

	cout<<"*********************"<<endl;
	cout<<"please enter the name:"<<endl;
	cout<<"*********************"<<endl;
	cin>>work[Work_Num].name;

	int num=Work_Num;
	Work_Num++;
	for(int i=0;i<m;i++)
	{
		if(free_table[i].flag==1)
		{
			if(free_table[i].length<work[num].length)
			{
				if(i==m-1)
				{
					cout<<"**************"<<endl;
					cout<<"*  WRONG!!!  *"<<endl;
					cout<<"**************"<<endl;
					cout<<"This work cannot be encased..."<<endl;
				}
				else
					continue;
			}
			else if(free_table[i].length==work[num].length)
			{
				free_table[i].flag=0;
				free_table[i].length=0;
				work[num].address=free_table[i].address;
				work[num].block=i;
				ShowSpace();
				return;
			}
			else
			{
			    work[num].address=free_table[i].address;
				free_table[i].length=free_table[i].length-work[num].length;
				free_table[i].address=free_table[i].address+work[num].length;
				work[num].block=i;
				ShowSpace();
				return;
			}
		}
		else
		{
			if(i==m-1)
			{
				cout<<"**************"<<endl;
				cout<<"*  WRONG!!!  *"<<endl;
				cout<<"**************"<<endl;
				cout<<"This work cannot be encased..."<<endl;
			}
			else
				continue;
		}

	}
}

void ShowUse()
{
	cout<<"WorkName"<<"\tWorkSpace"<<"\tStartSpace"<<"\tEndSpace"<<endl;
	for(int i=0;i<Work_Num;i++)
	{
		cout<<work[i].name<<"\t\t"<<work[i].length<<"\t\t"<<work[i].address<<"\t\t"<<work[i].address+work[i].length-1<<endl;
	}
	cout<<"The number of work is "<<Work_Num<<endl;
}

void findover()
{
	for(int j=0;j<Free_Num;j++)
    {
		for(int jj=0;jj<Free_Num;jj++)
              if(free_table[j].address+free_table[j].length==free_table[jj].address)
              {
                  free_table[j].length=free_table[j].length+free_table[jj].length;
                  free_table[jj].address=0;
                  free_table[jj].length=0;
                  free_table[jj].flag=0;
                  Free_Num--;
			break;
              }

     }
}

void findzero()
{
	for(int i=0;i<Free_Num;i++)
	{
		if(free_table[i].length==0)
		{
			for(int k=i;k<Free_Num;k++)
			{
				if(k<Free_Num-1)
					free_table[k]=free_table[k+1];
				else
				{
					free_table[k].length=0;
					free_table[k].address=0;
					free_table[k].flag=0;
				}	
			}
		}
	}
}

void Releash()
{
	string temp;
	cout<<"********************************"<<endl;
	cout<<"please enter the name to releash:"<<endl;
	cout<<"********************************"<<endl;
	cin>>temp;
	for(int i=0;i<Work_Num;i++)
	{
		if(work[i].name==temp)
		{
			free_table[Free_Num].address=work[i].address;
			free_table[Free_Num].length=free_table[Free_Num].length+work[i].length;
			free_table[Free_Num].flag=1;
            Free_Num++;
		
			cout<<work[i].name<<" is deleted"<<endl;
			findover();
			findzero();
			for(int k=i;k<Work_Num;k++)
			{
				if(k<Work_Num-1)
				work[k]=work[k+1];
				else
				break;
			}
			Work_Num--;
			break;
		}
	}
}

int main()
{
	int k;
	while(1)
	{
	    cout<<"\t\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
	    cout<<"\t\t|Weccome to the resource allocating system|"<<endl;
	    cout<<"\t\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl<<endl;
	    cout<<"\t\t************Input 1: Initialize the space"<<endl;
	    cout<<"\t\t************Input 2: Show a safe sequence"<<endl;
	    cout<<"\t\t************Input 3: Allocate the space"<<endl;
	    cout<<"\t\t************Input 4: Show the used space"<<endl;
		cout<<"\t\t************Input 5: Releash a process"<<endl;
	    cin>>k;
	    switch(k)
	    {
	        case 1:InitSpace();
				break;
			case 2:ShowSpace();
				break;
			case 3:AllocateSpace();
				break;
			case 4:ShowUse();
				break;
			case 5:Releash();
				break;
	    }
	}
	return 0;
}
