#include<iostream>
#include<stdlib.h>
#include<string>
#define coHappen 5
using namespace std;
const int B=0;
const int E=2;
const int R=1;
struct pcb
{
	char name[10];
	int required_time;
	int status;
    pcb* next;
};
pcb *A_head=new pcb,*A_tail=NULL,*B_head=new pcb,*B_tail=NULL;

void New()
{
	pcb *process=new pcb;
	pcb *L=A_head;
	int processnum=0;
	while(L->next!=NULL)
	{
		L=L->next;
		processnum=processnum+1;
		if(processnum>=coHappen)
		{
			cout<<"process fulfilled"<<endl;
			return;
		}
	}
	L->next=process;
	cout<<"please enter the name of the process:"<<endl;
	cin>>process->name;
	cout<<"please enter the required time of the process:"<<endl;
	cin>>process->required_time;
	process->status=R;
	process->next=NULL;
	A_tail=process;
	cout<<"successfully created"<<endl;
}

void Run_finish()
{

	if(A_head->next==NULL)
	{
		cout<<"No process in line"<<endl;
	}
	else
	{
		pcb *temp=A_head->next;
		A_head->next=A_head->next->next;
		cout<<temp->name<<" has been finished"<<endl;
	}
}

void Run_wait()
{
	if(A_head->next==NULL)
	{
		cout<<"No process in running line"<<endl;
	}
    else
    {
        pcb *temp=A_head->next;
        A_head->next=A_head->next->next;
        cout<<temp->name<<" is running"<<endl;
		cout<<"."<<endl<<"."<<endl<<"."<<endl<<"."<<endl<<"."<<endl;
        temp->status=B;
        cout<<temp->name<<" is blocked"<<endl;
        if(B_head->next==NULL)
        {
            B_head->next=temp;
            B_tail=temp;
        }
        else
        {
            B_tail->next=temp;
            B_tail=temp;
        }
        B_tail->next=NULL;
        cout<<"Block finished"<<endl;

    }

}



void Signal()
{
	if(B_head->next==NULL)
	{
		cout<<"No process in block line"<<endl;
	}
    else
    {
        pcb *temp=B_head->next;
        B_head->next=B_head->next->next;
        cout<<temp->name<<" is recovered"<<endl;
		A_tail->next=temp;
        A_tail=temp;
		temp->status=R;
		temp->next=NULL;
        cout<<"Recover from block finished"<<endl;

    }

}

void Show()
{
	cout<<"name\t\t"<<"time\t\t"<<"status\t\t"<<"pointer\t\t"<<endl;
	pcb *A_TEMP=A_head;
	pcb *B_TEMP=B_head;
	while(A_TEMP->next!=NULL)
	{
		A_TEMP=A_TEMP->next;
		cout<<A_TEMP->name<<"\t\t"<<A_TEMP->required_time<<"\t\t"<<A_TEMP->status<<"\t\t"<<A_TEMP->next<<"\t\t"<<endl;
	}
	while(B_TEMP->next!=NULL)
	{
		B_TEMP=B_TEMP->next;
		cout<<B_TEMP->name<<"\t\t"<<B_TEMP->required_time<<"\t\t"<<B_TEMP->status<<"\t\t"<<B_TEMP->next<<"\t\t"<<endl;
	}
}

int main()
{

	A_head->next=NULL;
	B_head->next=NULL;
	string line;
	while(1)
	{
			cout<<"***********************PCB controler***********************"<<endl;
		cout<<"1. To create a process"<<endl;
		cout<<"      Please input 'New'"<<endl;
		cout<<"2. To run and finish a process"<<endl;
		cout<<"      Please input 'Run(finish)'"<<endl;
		cout<<"3. To run and make a process wait"<<endl;
		cout<<"      Please input 'Run(wait)'"<<endl;
		cout<<"4. To awaken a process"<<endl;
		cout<<"      Please input 'Signal'"<<endl;
		cout<<"5. To show all the message in run"<<endl;
		cout<<"      Please input 'Show'"<<endl;
		cout<<"6. Exit"<<endl;
		cout<<"      Please input 'Exit'"<<endl;
		cin>>line;
		if(line=="New")
		{
			New();
		}
		else if(line=="Run(finish)")
		{
			Run_finish();
		}
		else if(line=="Run(wait)")
		{
			Run_wait();
		}
		else if(line=="Signal")
		{
			Signal();
		}
		else if(line=="Show")
		{
			Show();
		}
		else if(line=="Exit")
		{
			exit(0);
		}
		else
		{
			cout<<"error"<<endl;
		}
	}
}
