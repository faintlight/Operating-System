#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#define B 3
using namespace std;
int N;
struct
{
    int id;
    int state;
    int block;
}page[100];
struct
{
    int id;
    int number;
}block[B];

int opt=0,fifo=0,lru=0;
int a[20]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};

void secret()
{
	N=20;
    for(int i=0;i<N;i++)
    {
        page[i].id=a[i];
    }
    for(int j=0;j<B;j++)
    {
        block[j].id=j+1;
        block[j].number=-1;
    }
}
void SetSequence()
{
    int temp;
	cout<<"**********************please input the quantity: "<<endl;
    cin>>N;
	cout<<"**********************please input the number: "<<endl;
	for(int i=0;i<N;i++)
    {
        cin>>temp;
        page[i].id=temp;
        page[i].state=0;
    }
    for(int j=0;j<B;j++)
    {
        block[j].id=j+1;
        block[j].number=-1;
    }
}
void showN()
{
	cout<<N;
}

void init()
{
	 for(int kk=0;kk<B;kk++)
    {
        block[kk].number=-1;
    }	
}
void ShowOPT()
{
	init();
	opt=0;
	int j;
    cout<<"\tblock1\tblock2\tblock3\tinterruption"<<endl;
    for(int i=0;i<N;i++)
    {
        if(i<3)
        {
            page[i].block=block[i].id;
            page[i].state=1;
            block[i].number=page[i].id;
        }
        else if(block[0].number==page[i].id||block[1].number==page[i].id||block[2].number==page[i].id)
        {
            cout<<"page"<<i<<"\t"<<block[0].number<<"\t"<<block[1].number<<"\t"<<block[2].number<<"\tNO"<<endl;
            continue;
        }
        else
        {
            int temp1=100,temp2=100,temp3=100;
            for(int j=i+1;j<N;j++)
            {
                if(page[j].id==block[0].number)
                {
                    temp1=j;
                    break;
                }
            }
            for(j=i+1;j<N;j++)
            {
                if(page[j].id==block[1].number)
                {
                    temp2=j;
                    break;
                }
            }
            for(j=i+1;j<N;j++)
            {
                if(page[j].id==block[2].number)
                {
                    temp3=j;
                    break;
                }
            }
            if(temp1>temp2&&temp1>temp3)
            {
                page[i].state=1;
                page[i].block=0;
                block[0].number=page[i].id;
            }
            else if(temp2>temp1&&temp2>temp3)
            {
                page[i].state=1;
                page[i].block=1;
                block[1].number=page[i].id;
            }
            else
            {
                page[i].state=1;
                page[i].block=2;
                block[2].number=page[i].id;
            }
        }
        cout<<"page"<<i<<"\t"<<block[0].number<<"\t"<<block[1].number<<"\t"<<block[2].number<<"\tYES"<<endl;
        opt++;
    }
    cout<<"**********************opt: "<<opt<<endl;
    double rate=1.0*opt/N;
    cout<<"**********************missing page interruption rate: "<<rate<<endl;
}

void ShowFIFO()
{
	init();
	fifo=0;
    int count=0;
    cout<<"\tblock1\tblock2\tblock3\tinterruption"<<endl;
    for(int i=0;i<N;i++)
    {
        if(i<3)
        {
            page[i].block=block[i].id;
            page[i].state=1;
            block[i].number=page[i].id;
        }
        else if(block[0].number==page[i].id||block[1].number==page[i].id||block[2].number==page[i].id)
        {
            cout<<"page"<<i<<"\t"<<block[0].number<<"\t"<<block[1].number<<"\t"<<block[2].number<<"\tNO"<<endl;
            continue;
        }
        else
        {
            page[i].state=1;
            page[i].block=block[count].id;
            block[count].number=page[i].id;
            count++;
            if(count==3)
            {
                count=0;
            }
        }
        cout<<"page"<<i<<"\t"<<block[0].number<<"\t"<<block[1].number<<"\t"<<block[2].number<<"\tYES"<<endl;
        fifo++;
    }
    cout<<"**********************fifo: "<<fifo<<endl;
    double rate=1.0*fifo/N;
    cout<<"**********************missing page interruption rate: "<<rate<<endl;
}

void ShowLRU()
{
	init();
	lru=0;
	int j;
    int count=0;
    cout<<"\tblock1\tblock2\tblock3\tinterruption"<<endl;
    for(int i=0;i<N;i++)
    {
        if(i<3)
        {
            page[i].block=block[i].id;
            page[i].state=1;
            block[i].number=page[i].id;
        }
        else if(block[0].number==page[i].id||block[1].number==page[i].id||block[2].number==page[i].id)
        {
            cout<<"page"<<i<<"\t"<<block[0].number<<"\t"<<block[1].number<<"\t"<<block[2].number<<"\tNO"<<endl;
            continue;
        }
        else
        {
            int temp1=100,temp2=100,temp3=100;
            for(j=i-1;j>=0;j--)
            {
                if(page[j].id==block[0].number)
                {
                    temp1=j;
                    break;
                }
            }
            for(j=i-1;j>=0;j--)
            {
                if(page[j].id==block[1].number)
                {
                    temp2=j;
                    break;
                }
            }
            for(j=i-1;j>=0;j--)
            {
                if(page[j].id==block[2].number)
                {
                    temp3=j;
                    break;
                }
            }
            if(temp1<temp2&&temp1<temp3)
            {
                page[i].state=1;
                page[i].block=0;
                block[0].number=page[i].id;
            }
            else if(temp2<temp1&&temp2<temp3)
            {
                page[i].state=1;
                page[i].block=1;
                block[1].number=page[i].id;
            }
            else
            {
                page[i].state=1;
                page[i].block=2;
                block[2].number=page[i].id;
            }

        }
        cout<<"page"<<i<<"\t"<<block[0].number<<"\t"<<block[1].number<<"\t"<<block[2].number<<"\tYES"<<endl;
        lru++;
    }
    cout<<"**********************lru: "<<lru<<endl;
    double rate=1.0*lru/N;
    cout<<"**********************missing page interruption rate: "<<rate<<endl;
}

int min(int a,int b)
{
	return a>b?b:a;
}

void Choose()
{
    cout<<"--------"<<endl;
    cout<<"|fifo:"<<fifo<<endl;
    cout<<"--------"<<endl;
    cout<<"|opt:"<<opt<<endl;
    cout<<"--------"<<endl;
    cout<<"|lru:"<<lru<<endl;
    cout<<"--------"<<endl;
    if(fifo==min(min(fifo,lru),opt))
    {
        cout<<"The best algorithm is fifo"<<endl;
        return;
    }
    if(lru==min(min(fifo,lru),opt))
    {
        cout<<"The best algorithm is lru"<<endl;
        return;
    }
    if(opt==min(min(fifo,lru),opt))
    {
        cout<<"The best algorithm is opt"<<endl;
        return;
    }
}

int main()
{
    int k;
	while(1)
	{
	    cout<<"\t\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
	    cout<<"\t\t|Weccome to the missing page interruption system|"<<endl;
	    cout<<"\t\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl<<endl;
	    cout<<"\t\t************Input 1: Set the sequence number"<<endl;
	    cout<<"\t\t************Input 2: algorithm OPT"<<endl;
	    cout<<"\t\t************Input 3: algorithm FIFO"<<endl;
	    cout<<"\t\t************Input 4: algorithm LRU"<<endl;
		cout<<"\t\t************Input 5: Choose the BEST"<<endl;
	    cin>>k;
	    switch(k)
	    {
	        case 0:secret();
                break;
	        case 1:SetSequence();
				break;
			case 2:ShowOPT();showN();
				break;
			case 3:ShowFIFO();showN();
				break;
			case 4:ShowLRU();
				break;
			case 5:Choose();
				break;
	    }
	}
	return 0;
}
