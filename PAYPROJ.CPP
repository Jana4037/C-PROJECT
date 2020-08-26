#include<stdio.h>
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
class account
{ public:
  long int mobnum;
  char name[35],pw[20];
  float balance;
  void output();
  account()
  { mobnum=0;
   balance=0;
   }
};
void account::output()
{ cout<<"\n\t\t\tNAME           : ";puts(name);
  cout<<"\t\t\tACCOUNT NUMBER : "<<mobnum<<endl;
  cout<<"\t\t\tBALANCE        : "<<balance<<endl;
}
void pay(long int);
void addmoney(long int);
void recharge(long int);
void modify(long int);
void newuser();
void login();
void output(long int);


void newuser()
{ char name[35],passw[20];
  long int mnum;
  account a,b;
  int exist=0,ok=0,loop=1;
  fstream f1;
  f1.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
  clrscr();
  gotoxy(35,9);
  cout<<"NEW USER";
  cout<<"\n\n\n\t\t\t\tNAME: ";
  cin>>name;
  while(loop==1)
  {  loop=0;
     cout<<"\n\n\t\t\tMOBILE NUMBER : ";
     cin>>mnum;
     while(!f1.eof())
     {  f1.read((char*)&a,sizeof(a));
	if(a.mobnum==mnum)
	{ exist++;
	  break;
	}
     }
     if(exist==0)
     {
     cout<<"ENTER PASSWORD : ";
     gets(passw);
     ok++;
     }
     else
     { cout<<"THIS NO. IS NOT AVAILABLE PLS ENTER NEW NO. ";
      loop++;
     }
  }
  f1.close();
   fstream f2;
   f2.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
 if(ok==1)
 { strcpy(b.name,name);
   strcpy(b.pw,passw);
   b.mobnum=mnum;
   b.balance=0;
   f2.write((char*)&b,sizeof(b));
   cout<<"\nACCOUNT OPENED SUCESSFULLY!!!";
  }
  f2.close();
  login();


 }

 void login()
 {  int check=0;
    char passw[20];
    clrscr();
    gotoxy(27,7);
    cout<<"BHARATH PAYMENTS BANK\n\n";
    gotoxy(30,8);
    cout<<":::::::";
    gotoxy(30,9);
    cout<<" LOGIN";
    gotoxy(30,10);
    cout<<":::::::";
    long int mnum;
    cout<<"\nMOBILE NO.   :";cin>>mnum;
    cout<<"\nPASSWORD     :";gets(passw);
    account a;
    fstream f3;
    f3.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
    while(!f3.eof())
    { f3.read((char*)&a,sizeof(a));
      if((a.mobnum==mnum)&&(strcmp(a.pw,passw)==0))
      {  check=1;
	 break;
      }
     }
     f3.close();
     clrscr();
     int ch=0;
    if(check==1)
    {
      cout<<"ENTER  1-PAY\n\t2-ADD MONEY TO WALLET\n\t3-MODIFY ACCOUNT\n\t4-RECHARGE\n\t5-ACCOUNT DETAILS";
      cout<<"ENTER YOUR CHOICE  : ";
      cin>>ch;
      switch(ch)
      { case 1:pay(mnum);
	       break;
	case 2:addmoney(mnum);
	       break;
	case 3:modify(mnum);
	       break;
	case 4:recharge(mnum);
	       break;
	case 5:output(mnum);
	       break;
      };
    }
    else
    cout<<"no such account exist";
    getch();
 }
 void addmoney(long int mobno)
 {  float amt=0;
    long pos;
    int chk=0;
    account a;
    clrscr();
    gotoxy(30,9);
    cout<<"::::::::::::::::::::";
    gotoxy(30,10);
    cout<<"ADD MONEY TO WALLET";
    gotoxy(30,11);
    cout<<"::::::::::::::::::::";
    cout<<"\n\n\t\t\tENTER AMOUNT TO BE ADDED :";cin>>amt;
    fstream f4;
    f4.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
    f4.seekg(0);
    while(!f4.eof())
    { pos=f4.tellg();
      f4.read((char*)&a,sizeof(a));
      if(a.mobnum==mobno)
      {  a.balance=a.balance+amt;
	 f4.seekp(pos);
	 f4.write((char*)&a,sizeof(a));
	 chk=1;
	 a.output();
	 break;
      }
    }
    if(chk==1)
    cout<<"\t\t\tMONEY ADDED TO WALLET!!!!";
    getch();
 }
 void modify(long int mobno)
 {  int choice=0,check=0;
    long pos;
    clrscr();
    account a;
    char nname[35],npw[20];
    fstream f5;
    f5.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
    f5.seekg(0,ios::beg);
    gotoxy(30,8);
    cout<<"::::::::::::";
    gotoxy(30,9);
    cout<<"MODIFICATION";
    gotoxy(30,10);
    cout<<"::::::::::::";
    cout<<"\n\n\t\tENTER 1-MODIFY NAME\n\t\t2-MODIFY PASSWORD  :";
    cin>>choice;
    switch(choice)
    { case 1:cout<<"\n\t\tENTER NEW NAME :";
	     gets(nname);
	     while(!f5.eof())
	     { pos=f5.tellg();
	       f5.read((char*)&a,sizeof(a));
	       if(a.mobnum==mobno)
	       {  strcpy(a.name,nname);
		  f5.seekg(pos);
		  f5.write((char*)&a,sizeof(a));
		  check=1;
		  a.output();
		  f5.close();
		  break;
		}
	      }
	      break;
       case 2:cout<<"\nENTER NEW PASSWORD : ";
	      gets(npw);
	      while(!f5.eof())
	     { pos=f5.tellg();
	       f5.read((char*)&a,sizeof(a));
	       if(a.mobnum==mobno)
	       {  strcpy(a.pw,npw);
		  f5.seekg(pos);
		  f5.write((char*)&a,sizeof(a));

		  check=1;
		  a.output();
		  f5.close();
		  break;
		}
	      }
	      break;
	 default:cout<<"\ninvalid option";
		 break;
   };
   if(check==1)
   { gotoxy(100,25);
   cout<<"                         MODIFIED!!!!";
   }
   else
   cout<<"NOT MODIFIED";
   getch();
}
void recharge(long int mobno)
{ long int mobi;
  long pos;
  float amt=0;
  clrscr();
  gotoxy(30,9);
  cout<<"::::::::";
  gotoxy(30,10);
  cout<<"RECHARGE";
  gotoxy(30,11);
  cout<<"::::::::";
  cout<<"ENTER MOBILE NUMBER :";
  cin>>mobi;
    int chk=0;
    account a;
    cout<<"\n\n\t\tENTER AMOUNT TO BE RECHARGED :";cin>>amt;
    fstream f6;
    f6.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
    f6.seekg(0);
    while(!f6.eof())
    { pos=f6.tellg();
      f6.read((char*)&a,sizeof(a));
      if(a.mobnum==mobno)
      {  a.balance=a.balance-amt;
	 f6.seekp(pos);
	 f6.write((char*)&a,sizeof(a));
	 chk=1;
	 a.output();
	 break;
      }
    }
    if(chk==1)
    cout<<"RECHARGED!!!";
    getch();
 }
 void pay(long int mobno)
 { account a,b;
  long pos;
  int check=0;
  long int mp;
  float amt=0;
  gotoxy(30,9);
  cout<<"::::";
  gotoxy(30,10);
  cout<<"PAY";
  gotoxy(30,11);
  cout<<"::::";
  cout<<"\n\n\t\tENTER MOBILE NO. TO BE PAID : ";
  cin>>mp;
    fstream fa;
    fa.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
    while(!fa.eof())
    { fa.read((char*)&a,sizeof(a));
      if(a.mobnum==mp)
      { check=1;
	break;
      }
    }
    fa.close();
     fstream f9;
    f9.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
  if(check==1)
  { cout<<"\n\t\tENTER AMOUNT TO BE PAID :";cin>>amt;
    while(!f9.eof())
    { pos=f9.tellg();
      f9.read((char*)&b,sizeof(b));
      if(b.mobnum==mobno)
      {  b.balance=b.balance-amt;
	 f9.seekp(pos);
	 f9.write((char*)&b,sizeof(b));

	 b.output();
	 break;
	}
    }
    f9.close();
     fstream f8;
    f8.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
    while(!f8.eof())
    { pos=f8.tellg();
      f8.read((char*)&b,sizeof(b));
      if(b.mobnum==mp)
      {  b.balance=b.balance+amt;
	 f8.seekp(pos);
	 f8.write((char*)&b,sizeof(b));

	 b.output();
	 f8.close();
	 break;
	}
    }
  }
  else if (check!=1)
  cout<<"NO SUCH ACCIOUNT EXIST";
}
void output(long int mobno)
{  account b;
    fstream f7;
    f7.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
    while(!f7.eof())
    {  f7.read((char*)&b,sizeof(b));
      if(b.mobnum==mobno)
      {  b.output();
	f7.close();
       break;
      }
    }
}
void admin()
{clrscr();
 int pw,id;
 gotoxy( 30,8);
 cout<<":::::";
 gotoxy(30,9);
 cout<<"ADMIN";
 gotoxy(30,10);
 cout<<":::::";
 cout<<"\n\t\t\tADMIN ID : ";
 cin>>id;
 cout<<"\n\t\t\tPIN      : ";
 cin>>pw;
 if((id==123)&&(pw==123))
 {    account b;
    fstream fb;
    fb.open("paypro.txt",ios::binary|ios::app|ios::in|ios::out);
    while(!fb.eof())
    {  fb.read((char*)&b,sizeof(b));
       b.output();
     }
     fb.close();
     getch();
 }
 }
void main()
{  clrscr();
   gotoxy(20,6);
   cout<<"BHARATH PAYMENTS BANK";
    int choice=0;
    char ch='y';

    while((ch=='y')||(ch=='Y'))
    {  cout<<"\n\n\tENTER 1-CREATE NEW ACCOUNT \n\t\t\t2-LOGIN\n\t\t\t3-ADMIN\t :";
       cin>>choice;
      if(choice==1)
      {
      newuser();
      }
      else if(choice==2)
      {
      login();
      }
      else if (choice==3)
      { admin();
      }
      else
      {
      cout<<"invalid choice ";
      break;
      }
      cout<<"\n\ndo you want to continue???enter y-yes : ";
      cin>>ch;
     }

}