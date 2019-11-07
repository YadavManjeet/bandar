//               Header   files   used
 
#include<iostream>
#include<conio.h>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//**************************************************************
//                CLASS
 
 class account
 {
     int acc_no ;    //  account number 
     char name[50];
     int  deposit ;
     char type ; // type of account saving or current


   public :
        void create_acc();      //function used to add data of user 
         void show_acc() const ;    // function used to show data 
         void modify( );      //  function used to add new data 
         void  dep( int );     //function used to  accept amount  
         void draw(int);      // function used to withdraw amount
         
         void  report() const;
         int retacc_no() const;
         int retdep() const ;       // function used to return balance amount
         char rettype() const ;   //  return type of account 
 };
 
  //  class end 
void intro(); 
void  account :: create_acc()
 {
     cout<<"\nEnter account number : ";
          
cin>>acc_no;
     cout<<"\nEnter account holder name : ";
     cin.ignore();
     cin.getline(name,50);
     cout<<"\nEnter account type (s for saving && c for current )  : ";
     cin>>type;
     type =toupper(type);                               //    used to make alphabet capital
     cout<<"\nEnter the Initial amount  : ";
     cin>>deposit;
     cout<<" \n\n\n\t\t     Account Created \n\n";
     
 }
  void account :: show_acc() const
  {
      cout<<"\n ACCOUNT No. : "<<acc_no;
      cout<<"\n ACCOUNT HOLDER NAME : "<<name;
      cout<<"\n TYPE OF ACCOUNT : "<<type;
    
   cout<<"\n Balance amount : "<<deposit;
   }
   void account :: modify()
   {
     cout<<"\nAccount Number :"<<acc_no;
     cout<<"\nModify account holder name : ";
     cin.ignore();
     cin.getline(name,50);
     cout<<"\nModify Type of Account (You can SWAP  <S> to <C> or vice versa )  :";
     cin>>type;
     type=toupper(type);
     
 }
 
 void account :: dep(int x )
 {
     deposit +=x;
   }

void account :: draw(int x)
 {
     deposit -=x;
 }
 void account :: report( ) const
 {
     cout<<setw(10)<<acc_no<<setw(16)<<name<<setw(6)<<type<<setw(10)<<deposit<<endl;
     
 }
 int account :: retacc_no() const
 {
     return acc_no;
 }
 int account :: retdep() const
 {
     return deposit;
   } 
 
 
char account :: rettype() const
 {
     return type;
 }
 
 //  Declare function for binary file 
    
void write_acc();            // wirte record on binary file
void display(int);               // display account detail
void modify_acc(int);        // modify record
void delete_acc(int);         // delete record
void display_all( );           // display all account
void dep_withdraw(int,int);           //    for  deposit and withdraw   



//**************************************************************
//**************************************************************
//                             Main function start 
               
 int main()
 {
     char ch;
     int num;
     intro();
     do
     {
         cout<<"\n\nMAIN MENU ";
         cout<<"\n\n\n1. NEW ACCOUNT ";
         cout<<"\n\n2. DEPOSIT AMOUNT ";
         cout<<"\n\n3. WITHDRAW AMOUNT ";
         cout<<"\n\n4. BALANCE INQUIRY ";
         cout<<"\n\n5. ALL ACCOUNT HOLDER LIST ";
         cout<<"\n\n6. CLOSE AN ACCOUNT ";
         cout<<"\n\n7. MODIFY ACCOUNT "; 
         cout<<"\n\n8. EXIT ";
        

       
         cout<<"\n\n\nSelect any option from(1-8)  : ";
         cin>>ch;
          
          switch(ch)
          {
        case '1' :
              write_acc();
              break;
        case '2':
              cout<<"\n\n\nEnter account number : ";
              cin>>num;
              dep_withdraw(num,1);
              break;
         case '3' :
              cout<<"\n\nEnter the account number : ";
              cin>>num;
              dep_withdraw(num,2);
              break;
         case '4' :
              cout<<"\n\nEnter the account number : ";
              

         cin>>num;
              display(num);
              break;
         case '5' :
               display_all();
               break;
         case  '6' :
                cout<<"\n\nEnter the account number " ;
                 cin>>num;
                  delete_acc(num);   
                  break;
        case '7' :
                   cout<<"\n\nEnter the account number " ;
                    cin>>num;
                    modify_acc(num);
                    break;
        case '8' :
                   cout<<" \n\n\nTHANKS ";
                   break;
         
           default : 
                    cout<<" \a";         //alert 
            }
           cin.ignore();
           cin.get();
           }while(ch!='8');
           return 0; 
     }
//**********************************************************************************************************
//                                FUNCTION TO WRITE IN FILE 


void write_acc()
{
    account ac;
    ofstream ofile;
    ofile.open("account.dat",ios :: binary | ios :: app);
    ac.create_acc();
    ofile.write(reinterpret_cast<char *>(&ac) , sizeof(account));
   
   ofile.close();
  }
//**************************************************************
//**************************************************************
//                              FUNCTION USED TO  DISPLAY  ANY RECORD

void display(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat", ios:: binary);
    if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
            }
           cout<<"\nBALANCE DETAILS\n";

    
  while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
     {
         if(ac.retacc_no()==n)
             {
                 ac.show_acc( );
                 flag=true;
       }
      }
     inFile.close();
     if(flag==false)
     cout<<"\n\nAccount number does not exist";

}
//*******************************************************************************************************
//    	Function to modify record of file

void modify_acc(int n)
 {
    bool found=false;
    account ac;
   


    fstream File;
    File.open("account.dat",ios :: binary | ios::in|ios::out);
    if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
       }
       while(!File.eof() && found==false)
     {
       File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacc_no()==n)
      {
           ac.show_acc();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
            }
       



 
       }
        File.close();
       if(found==false)
         cout<<"\n\n Record Not Found ";
}
//*************************************************************
//    	Function to delete record of file

void delete_acc(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios :: binary);
    if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        outFile.open("Temp.dat", ios :: binary);
        




       inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
       {
         if(ac.retacc_no()!=n)
            {
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
                }
                }
      inFile.close();
      outFile.close();
       remove("account.dat");
      rename("Temp.dat","account.dat");
     cout<<"\n\n\tRecord Deleted ..";
}
//************************************************************
//    	Function to display all accounts deposit list
void display_all()
 {
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios :: binary);


if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
        }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"--------------------------------------------------------------------------\n";
    cout<<setw(10)<<"A/c  no."<<setw(16)<<"NAME"<<setw(6)<<"Type"<<setw(10) <<"Balance\n";
    cout<<"---------------------------------------------------------------------------\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            ac.report();
        }
    
 inFile.close();
}

//******************************************************************************************************
//    	            Function to deposit and withdraw amounts





void dep_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios :: binary| ios::in|ios::out);
    if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
         }
    while(!File.eof() && found==false)
      {
          File.read(reinterpret_cast<char *> (&ac), sizeof(account));
          if(ac.retacc_no()==n)
              {
                  ac.show_acc();
                  if(option==1)
                      {
                          cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                        
               cout<<"\n\nEnter The amount to be deposited : ";
                          cin>>amt;
                          ac.dep(amt);
                      }
                      if(option==2)
              {
                 cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                 cout<<"\n\nEnter The amount to be withdraw : ";
                 cin>>amt;
                int bal=ac.retdep()-amt;
                 if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                     cout<<"Insufficience balance ";
                 else
                    ac.draw(amt);
               }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
           
 
   }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}
//**************************************************************
//    	INTRODUCTION FUNCTION

void intro()
{
    cout<<"\n\n\n BANK";
    cout<<"\n\n\n MANAGEMENT";
    cout<<"\n\n\n SYSTEM";
    cout<<"\n\n\n\nMADE BY :  MANJEET YADAV ";
    cout<<"\n\nCLASS : "<<setw(4)<<" CSE - A ";
    cin.get();
}
//*******************************************************
//                                                        END     OF     PROJECT
//*******************************************************

