#include<iostream>
#include<string>
#include<stdlib.h>
#include<cstring>
using namespace std;
int ANum,BNum,CNum;
int PNum=0;
int Available[3]={3,3,2};
int finished[50];
int finishnum=0;
int ss[50];
int ssnum=0;
struct Prcs
{
	int Max[50][3];
	int Allocation[50][3];
	int Need[50][3];
	string status;
};
Prcs process[10];
void Set_Max_ABC()
{
	cout<<"**********************************"<<endl;
	cout<<"Please input the value of MAX ABC:"<<endl;
	cout<<"Please input A:"<<endl;
	cin>>ANum;
	cout<<"Please input B:"<<endl;
	cin>>BNum;
	cout<<"Please input C:"<<endl;\
	cin>>CNum;
	cout<<"**********************************"<<endl;

	cout<<"*****************************"<<endl;
	cout<<"MAX ABC created successfully"<<endl;
	cout<<"*****************************"<<endl;
}
void Set_Max()
{
	for(int i=0;i<3;i++)
	{
		cin>>process[PNum].Max[PNum][i];
	}
}
void Set_Allocation()
{
	for(int i=0;i<3;i++)
	{
		cin>>process[PNum].Allocation[PNum][i];
	}
}
void Set_Need()
{
	for(int i=0;i<3;i++)
	{
		cin>>process[PNum].Need[PNum][i];
	}
}
void Set_Status()
{
    process[PNum].status="unfinished";
}
void createP()
{
    cout<<"|creating process"<<PNum<<":|"<<endl;
	cout<<"                    *****************************"<<endl;
	cout<<"                    Please input the MAX source:"<<endl;
	cout<<"                    *****************************"<<endl;
	Set_Max();
	cout<<"                    *****************************"<<endl;
	cout<<"                    Please input the ALLOCATED source:"<<endl;
	cout<<"                    *****************************"<<endl;
	Set_Allocation();
	cout<<"                    *****************************"<<endl;
	cout<<"                    Please input the NEEDED source:"<<endl;
	cout<<"                    *****************************"<<endl;
	Set_Need();
	Set_Status();
	PNum++;
	cout<<"*****************************"<<endl;
	cout<<"process created successfully"<<endl;
	cout<<"*****************************"<<endl;
}
int IsNotFinished(int i,int a[])
{
    for(int k=0;k<finishnum;k++)
    {
        if(a[k]==i)
            return 0;
    }
    return 1;
}
int Show_Sequence()
{
    int a=Available[0];
    int b=Available[1];
    int c=Available[2];
    int t=PNum;
    int flag=0;
	cout<<"process"<<"\t\tNEED"<<"\t\tALLOCATION"<<"\tALLOCATION+AVAILABLE"<<"\tSTATUS"<<endl;
    while(t)
    {
        flag=0;
        for(int i=0;i<PNum;i++)
        {
            if((a>=process[i].Need[i][0])&&
               (b>=process[i].Need[i][1])&&
               (c>=process[i].Need[i][2])&&
               IsNotFinished(i,finished))
            {
                finished[finishnum++]=i;
                a=a+process[i].Allocation[i][0];
                b=b+process[i].Allocation[i][1];
                c=c+process[i].Allocation[i][2];
                flag=1;
				ss[ssnum++]=i;
				
				cout<<"process"<<i<<"\t";
				cout<<"|"<<process[i].Need[i][0]<<"  "<<process[i].Need[i][1]<<"  "<<process[i].Need[i][2]<<"|\t";
				cout<<"|"<<process[i].Allocation[i][0]<<"  "<<process[i].Allocation[i][1]<<"  "<<process[i].Allocation[i][2]<<"|\t";
				cout<<"|"<<a<<"  "<<b<<"  "<<c<<"|\t";
				cout<<"|"<<"finished"<<"|"<<endl;

                break;
            }
            else
            {
                if(IsNotFinished(i,finished))
				continue;
            }
        }
        if(!flag)
        {
            cout<<"****************ALERT!!!!!!*************"<<endl;
            cout<<"****************"<<endl;
            cout<<"No safe sequence"<<endl;
            cout<<"****************"<<endl;
            finishnum=0;
            memset(finished,-1,sizeof(finished));
            return 0;
        }
        t--;
    }
    finishnum=0;
    memset(finished,-1,sizeof(finished));
	cout<<"safe sequence:"<<endl;
	for(int i=0;i<PNum;i++)
	{
		cout<<"process"<<ss[i]<<endl;
	}
    return 1;
}

void Do_Sequence()
{
    int a=Available[0];
    int b=Available[1];
    int c=Available[2];
    int t=PNum;
    int flag=0;
    while(t)
    {
        flag=0;
        for(int i=0;i<PNum;i++)
        {
            if((a>=process[i].Need[i][0])&&
               (b>=process[i].Need[i][1])&&
               (c>=process[i].Need[i][2])&&
               IsNotFinished(i,finished))
            {
                finished[finishnum++]=i;
                a=a+process[i].Allocation[i][0];
                b=b+process[i].Allocation[i][1];
                c=c+process[i].Allocation[i][2];
                process[i].status="finished";
                flag=1;
                break;
            }
        }
        if(!flag)
        {
            cout<<"****************ALERT!!!!!!*************"<<endl;
            cout<<"****************"<<endl;
            cout<<"No safe sequence"<<endl;
            cout<<"****************"<<endl;
            return;
        }
        t--;
    }
	cout<<"All the process is finished"<<endl;
}

void Show()
{
    cout<<"process"<<"\t\tMAX"<<"\t\tALLOCATION"<<"\tNEED"<<"\t\tSTATUS"<<endl;
	for(int i=0;i<PNum;i++)
	{
		cout<<"process"<<i<<"\t|"<<process[i].Max[i][0]<<"  "<<process[i].Max[i][1]<<"  "<<process[i].Max[i][2]<<"|\t";
		cout<<"|"<<process[i].Allocation[i][0]<<"  "<<process[i].Allocation[i][1]<<"  "<<process[i].Allocation[i][2]<<"|\t";
		cout<<"|"<<process[i].Need[i][0]<<"  "<<process[i].Need[i][1]<<"  "<<process[i].Need[i][2]<<"|\t";
		cout<<"|"<<process[i].status<<"|"<<endl;
	}
}

void Requesting(int i,int a,int b,int c)
{
	for(int j=0;j<PNum;j++)
	{
		process[j].status="unfinished";
	}
    if(a<=process[i].Need[i][0]&&b<=process[i].Need[i][1]&&c<=process[i].Need[i][2])
    {
        if(a<=Available[0]&&b<=Available[1]&&c<=Available[2])
        {
            Available[0]=Available[0]-a;
            Available[1]=Available[1]-b;
            Available[2]=Available[2]-c;
            process[i].Allocation[i][0]=process[i].Allocation[i][0]+a;
            process[i].Allocation[i][1]=process[i].Allocation[i][1]+b;
            process[i].Allocation[i][2]=process[i].Allocation[i][2]+c;
            process[i].Need[i][0]=process[i].Need[i][0]-a;
            process[i].Need[i][1]=process[i].Need[i][1]-b;
            process[i].Need[i][2]=process[i].Need[i][2]-c;
            if(Show_Sequence())
            {
                Do_Sequence();
            }
            else
            {
                cout<<"******************"<<endl;
                cout<<"restart the source"<<endl;
                cout<<"******************"<<endl;
                Available[0]=Available[0]+a;
                Available[1]=Available[1]+b;
                Available[2]=Available[2]+c;
                process[i].Allocation[i][0]=process[i].Allocation[i][0]-a;
                process[i].Allocation[i][1]=process[i].Allocation[i][1]-b;
                process[i].Allocation[i][2]=process[i].Allocation[i][2]-c;
                process[i].Need[i][0]=process[i].Need[i][0]+a;
                process[i].Need[i][1]=process[i].Need[i][1]+b;
                process[i].Need[i][2]=process[i].Need[i][2]+c;
            }
        }
        else
        {
            process[i].status="BLOCK";
            cout<<"********************"<<endl;
            cout<<"process"<<i<<" should wait"<<endl;
            cout<<"********************"<<endl;
        }
    }
    else
    {
        cout<<"******************"<<endl;
        cout<<"No enough resourse"<<endl;
        cout<<"******************"<<endl;
    }
}
void ShowAvailable()
{
	cout<<"resource 1:"<<Available[0]<<endl;
	cout<<"resource 2:"<<Available[1]<<endl;
	cout<<"resource 3:"<<Available[2]<<endl;
}
void Request()
{
	int i;
    int a,b,c;
    cout<<"                    *************************"<<endl;
	cout<<"                    The number of the process:"<<endl;
	cout<<"                    *************************"<<endl;
	cin>>i;
	cout<<"                    **********************************"<<endl;
	cout<<"                    Please input the request resource:"<<endl;
	cout<<"                    **********************************"<<endl;
	cin>>a>>b>>c;
    Requesting(i,a,b,c);
}
int main()
{
	Set_Max_ABC();
	int k;
	while(1)
	{
	    cout<<"\t\t\t\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
	    cout<<"\t\t\t\t|Welcome to the resource allocating system|"<<endl;
	    cout<<"\t\t\t\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl<<endl;
	    cout<<"\t\t\t\t************Input 1: Create a process"<<endl;
	    cout<<"\t\t\t\t************Input 2: Show a safe sequence"<<endl;
	    cout<<"\t\t\t\t************Input 3: Request the source"<<endl;
	    cout<<"\t\t\t\t************Input 4: Show the whole process"<<endl;
		cout<<"\t\t\t\t************Input 5: Show the available num"<<endl;
	    cin>>k;
	    switch(k)
	    {
	        case 1:createP();
	        break;
	        case 2:Show_Sequence();
	        break;
	        case 3:Request();
	        break;
	        case 4:Show();
	        break;
			case 5:ShowAvailable();
	        break;
	    }
	}
	return 0;
}
