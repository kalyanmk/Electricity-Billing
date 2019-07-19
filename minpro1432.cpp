#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
using namespace std;

void dispchar(char a,int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<a;
	}
}

class electricity
{
	public:
		int c_no , c_adhar;
		char c_name[20];
		public:
		void create();
		void display();
		void search();
		int check();
		electricity* operator ->()
		{
			return this;
		}
};

class calculate : public electricity
{ 
	public:
			int start,end,units;
			char pay[10];
	public:
	void paybill();
	friend void tariffdisp();
};

int check_duplicate_c_no(int cno)
{
	electricity l1;
	ifstream ftotal;
	ftotal.open("Electricity\\total.txt",ios::in|ios::binary);
	while(ftotal.read((char*)&l1,sizeof(l1)))
	{
		if(l1.c_no==cno)
		{
			ftotal.close();
			return(0);
		}
	}
	ftotal.close();
	return(1);
}

void electricity::create()
{
		electricity s1;
	
	    ofstream ftotal;
	    ftotal.open("Electricity\\total.txt",ios::app|ios::binary);
	
			cout<<"Enter the customer number:";
			cin>>s1.c_no;
				if(check_duplicate_c_no(s1.c_no))
				{
				cout<<"Enter the customer name:";
				cin>>s1.c_name;
				cout<<"Enter the aadhaar number:";
				cin>>s1.c_adhar;	
				ftotal.write((char*)&s1,sizeof(s1));
				ftotal.close();
				cout<<"\n\n";
				system("pause");
				}
				else
				{
					cout<<"Already Customer  with same number is present\n";
					system("pause");
				}
}

void electricity::display()
{
	int choice;
	electricity s1;
	calculate s2;

	ifstream ftotal,fstatus;
	ftotal.open("Electricity\\total.txt",ios::in|ios::binary);
	fstatus.open("Electricity\\status.txt",ios::in|ios::binary);
	
	dispchar('*',79);
	cout<<"\n\t\t\tWHAT DO YOU WANT TO SEE\n";
	dispchar('*',79);
	
	cout<<"\n\n1:List of Customers\n2:Payment Status\n\t";
	cin>>choice;
	
	if(choice==1)
	{
		system("cls");
		
		dispchar('*',79);
		cout<<"\n\t\t\t\t   LIST OF ALL CUSTOMERS\n";
		dispchar('*',79);
		
		cout<<"\n\n\nC_no \tCustomer_name\tCustomer Aadhaar\n\n";
		while(ftotal.read((char*)&s1,sizeof(s1)))
		{
		       cout<<s1.c_no<<"\t\t"<<s1.c_name<<"\t\t"<<s1.c_adhar<<"\t\t"<<"\n";
		}
		ftotal.close();
	}
	else if(choice==2)
	{
		system("cls");
		
		dispchar('*',79);
		cout<<"\n\t\t\t\t\tCUSTOMER PAYMENT STATUS\n";
		dispchar('*',79);
		
		cout<<"\n\n\nC_NO.\t\tCUSTOMER_NAME\tUNITS\tPAYMENT STATUS\n\n";
		while(fstatus.read((char*)&s2,sizeof(s2)))
		{
		       cout<<s2.c_no<<"\t\t"<<s2.c_name<<"\t\t"<<s2.units<<"\t"<<s2.pay<<"\n";
		}
		fstatus.close();
	}
	else
	cout<<"\n\nINVALID INPUT";
	getch();
}

void electricity::search()
{
	int found=0;
	int cno;
	calculate s1;
	ifstream ftotal;
	
	ftotal.open("Electricity\\status.txt",ios::in|ios::binary);
	
	cout<<"\n\n\tEnter Customer No. to seach : ";
	cin>>cno;
	

	while(ftotal.read((char*)&s1,sizeof(s1)))
	{
		if(cno==s1.c_no)
		{
				cout<<"\n\n\nCustomer No.\tCustomer Name\tUnits\tStatus\n\n";
				cout<<s1.c_no<<"\t\t"<<s1.c_name<<"\t\t"<<s1.units<<"\t\t"<<s1.pay<<"\n";
				found=1;
			
		}
	}
	
	ftotal.close();
	if(found==0)
	cout<<"customer with customer no. "<<cno<<" is not found"<<"\n\n\n\n\n";
	system("pause");
}

void calculate::paybill()
	{    
		int count=0,c_no,a;
		electricity l1;
		calculate c1;
		ifstream fin;
		ofstream fout;
	 	fout.open("Electricity\\status.txt",ios::app|ios::binary);
		fin.open("Electricity\\total.txt",ios::in|ios::binary);   

			system("cls");
			cout<<"Enter the customer number:";
			cin>>c_no;
			
			while(fin.read((char*)&l1,sizeof(l1)))
			{
			if(l1.c_no==c_no)
			{
			c1.c_no = l1.c_no;
			strcpy(c1.c_name , l1.c_name);
			c1.c_adhar = l1.c_adhar;
			
			cout<<"Enter the initial reading:";
			cin>>c1.start;
			cout<<"Enter the final reading:";
			cin>>c1.end;
			c1.units=c1.end-c1.start;
			
		    cout<<"****************Customer details***************";
			cout<<"\nCustomer number:"<<c1.c_no;
			cout<<"\nCustomer name:"<<c1.c_name;
			cout<<"\nCustomer adhar:"<<c1.c_adhar;
			cout<<"\nUnits consumed:"<<c1.units;
			cout<<"\nBill amount:\n";
			if(c1.units<=30)
			{
				cout<<c1.units<<"		"<<"3.25"<<"		"<<c1.units*3.25<<"\n";
				cout<<c1.units<<"		"<<"0.15"<<"		"<<c1.units*0.15<<"\n";
				cout<<"Total amount:"<<(c1.units*3.25)+(c1.units*0.15);
			}	
			else if(c1.units<=100)
			{
				cout<<"30"<<"		"<<"3.25"<<"		"<<30*3.25<<"\n";	
				cout<<c1.units-30<<"		"<<"4.70"<<"		"<<((c1.units-30)*4.70)<<"\n";
				cout<<c1.units<<"		"<<"0.15"<<"		"<<c1.units*0.15<<"\n";
				cout<<"Total amount:"<<(30*3.25)+((c1.units-30)*4.70)+(c1.units*0.15)<<"\n";
			}
			else if(c1.units<=200)
			{
				cout<<"30"<<"		"<<"3.25"<<"		"<<30*3.25<<"\n";	
				cout<<"70"<<"		"<<"4.70"<<"		"<<(70*4.70)<<"\n";
				cout<<c1.units-100<<"		"<<"6.25"<<"		"<<(c1.units-100)*6.25<<"\n";
				cout<<c1.units<<"		"<<"0.15"<<"		"<<c1.units*0.15<<"\n";
				cout<<"Total amount:"<<(30*3.25)+(70*4.70)+((c1.units-100)*6.25)+(c1.units*0.15)<<"\n";
			}
			else if(c1.units>200)
			{
				cout<<"30"<<"		"<<"3.25"<<"		"<<30*3.25<<"\n";	
				cout<<"70"<<"		"<<"4.70"<<"		"<<(70*4.70)<<"\n";
				cout<<"100"<<"		"<<"6.25"<<"		"<<(100)*6.25<<"\n";
				cout<<c1.units-200<<"		"<<"7.30"<<"		"<<((c1.units-200)*7.30)<<"\n";
				cout<<c1.units<<"		"<<"0.15"<<"		"<<c1.units*0.15<<"\n";
				cout<<"\n\nTotal amount:"<<(30*3.25)+(70*4.70)+((100)*6.25)+((c1.units-200)*7.30)+(c1.units*0.15)<<"\n";
			}
			
				cout<<"\n\nAre you willing to pay now?\nPress \nYes\nNo";
				cin>>c1.pay;
			
			 fout.write((char*)&c1,sizeof(c1));
			 fout.close();
			 count=1;
			}	
		}
		fin.close();

		if(count==0)
		{
			cout<<"\n\n\n\t\tcustomer number is wrong\n";
		}
	
			system("pause");
}
	 
void traiffdisp()
{
	cout<<"\n\n\t\t\t*************BESCOM**************\n\n\t\t\tFirst 30 units\t     :  Rs 3.25\n\t\t\tUpto next 70 units   :\tRs 4.70\n\t\t\tUpto next 100 units  :\tRs 6.25\n\t\t\tAbove 200 units\t     :  Rs 7.30\n\t\t\tPer unit\t     :  Rs 0.15";
	cout<<"\n\n\n\n\n\n\n\n";
	system("pause");
}

int password(char a[25])																//password function
{
	char pwd[25], ch;
	int i=0;
	cout<<"Enter password : ";
	while (1) 
	{
		ch = getch();
		
		if (ch == 13)  																	//13 is ASCII value of ENTER
		{
			pwd[i]='\0';
			break;
		}
		
		if (ch==8) 																	    //8 is ASCII value of BACKSPACE
		{
			if(i==0)																	//when i=0 it will not accept BACKSPACE
			{
        		continue;
			}
			else
			{
				cout<<"\b \b";
        		i--;
        		continue;
			}			
    	}
    	pwd[i++] = ch;
    	cout<<"*";
   }
	if(strcmp(a,pwd)==0)
	return(1);
	else
	return(0);
}
int main()
{     
	electricity l1; 
	calculate c1; 
	int a_choice=1,u_choice=1,ch=0;
	char pwd[25]="admin123";
	
	while(1)
	{
		system("cls");
		a_choice=1;
		cout<<"\n\t\t\t      ELECTRICITY BILLING\n";
		cout<<"\n\n1: Admin \n2: User \n3: Exit\nEnter choice : ";
		cin>>ch;
		if(ch==1)
		{
			if(password(pwd))
			{
				while(a_choice!=4)
				{
					system("cls");
					cout<<"\n   1.Create customer";
					cout<<"\n   2.Display ";
					cout<<"\n   3.Search customer";
					cout<<"\n   4.Exit\n";
					
					cin>>a_choice;
					
					if(a_choice==1)
					{
						l1->create();
					}
					else if(a_choice==2)
					{
						l1->display();
						
					}
					else if(a_choice==3)
					{
						l1->search();
					}
				}
			}
			else
			cout<<"\n\nIncorrect pwd\n\n";
			getch();
		}
		
			else if(ch==2)
		{
			while(u_choice!=3)
				{
					system("cls");
					cout<<"\n   1.Tariff";
					cout<<"\n   2.Pay bill";
					cout<<"\n   3.Exit\n";
					
					cin>>u_choice;
					
					if(u_choice==1)
					{    system("CLS");
						traiffdisp();	
					}
					else if(u_choice==2)
					{
						c1.paybill();
					}
					getch();
				}
		}
		else if(ch==3)
		{
			cout<<"\n\n\t\t\t\tBYE HAVE A NICE DAY\n";
			exit(0);
		}
		else
		{
			cout<<"\n\nInvalid\n\n";
		}
		getch();
		}
}
