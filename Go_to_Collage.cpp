#include<iostream>
#include<fstream>
#include <string>
#include <ctime>
#include<windows.h>

using namespace std;
int selectedstop;
class bus
{
    int index;
    int bustime;
    int busno;
    public:
        void stopdisplay();
        void searchbus();
        int askingstop();
        int askingtime();
        void display(int t,int no);

};
void bus::stopdisplay()
{
    fstream newfile;


   newfile.open("stop.txt",ios::in); 
   if (newfile.is_open()){ 
      string tp;
      while(getline(newfile, tp))
	  { 
	  
	  system("Color BC");
         cout <<"\t\t\t"<< tp << "\n"; 
      }
      newfile.close();
   }


}
int checktime(int time)
{
    int minutes=time%100;
    if(minutes>=60)
    return 0;
    minutes/=100;
    int hours = minutes;
    if(hours>=24)
        return 0;

    return 1;
}

int bus::askingtime()
{
	
    here:
    int choice;
    cout<<"***************************\n";
    cout<<"\nEnter 1 for Custom Time in HHMM(24-hr) Format"<<endl;
    cout<<"Enter 2 for Current Time \n ";
    cout<<"***************************\n";
    cout<<"Enter 0 to Return to Bus Stops:-";
    cin>>choice;
    if(choice==0)
    {
    	system("cls");
    	bus x;
    	x.stopdisplay();
    	goto here;
	}
	 
     else if(choice<1 || choice>2)
    {
        cout<<"PLEASE ENTER VALID CHOICE!";
        goto here;
    }
    switch(choice)
    {
        case 1:
               int customtime;
               cout<<"\nEnter Time :-";
               cin>>customtime;
               cout<<endl;
               checktime(customtime);
               return customtime;
               break;

        case 2:
            //logic to return current time

                   time_t now = time(0);
                   tm *ltm = localtime(&now);

                   int hours=ltm->tm_hour;
                   int minutes=ltm->tm_min;

                  // cout<<"Hours:"<<hours<<endl;

                  int finaltime;
                  // cout<<"Min:"<<min;
                   if(minutes<10)
                   finaltime=(hours*100)+(minutes);
                   else finaltime=(hours*100)+(minutes);
                   return finaltime;
                    break;








            //logic for default case
    };
}

void bus::display(int t,int no)
{
	int am;
    cout<<endl;
    int minutes=t%100;
    int hours;
    
    system("Color BD");
    t/=100;
    hours=t;
    if(hours>=12)
    am=0;
    else am=1;
    if(t!=12)
    hours=(t%12);
    else hours=12;
    if(minutes<10)
    cout<<"Time:- "<<hours<<":0"<<minutes<<" ";
    else
    cout<<"Time:- "<<hours<<":"<<minutes<<" ";
    if(am)
    cout<<"AM";
    else cout<<"PM";
    
    cout<<"\t\t";

    cout<<"BusNo.:- "<<no<<endl;
    cout<<endl;


}

void bus::searchbus()
{
    int s;
    cout<<"\nEnter Stop No. :- ";
   cin>>s;
   selectedstop=s;
   if(s>21)
   {
       s=21;
   }
   cout<<"\n\n";
	system("cls");
    ifstream x("bustiming.txt");

    index=s;
    int ctime=-1;
    there:
    ctime=askingtime();
    if(ctime>=2400 || ctime%100 >=60)
    {
    	cout<<"Enter Valid Time in 24-HR Format:\n";
    	goto there;
	}
    if(ctime==-1)
    return ;
	system("CLS");
	
	cout<<"TIMINGS AND BUS NO."<<endl<<endl;
	
    //index =1 trikon   time=0650
    while(!x.eof())
    {
        x>>index;
        x>>bustime;
        x>>busno;
        if(index!=-1 && bustime!=-1 && busno!=-1  && bustime>=ctime && index==s)
        {
        	
            display(bustime,busno);
            //1600->4:00
        }

    }
    return;
    x.close();

}

int main()
{
	system("Color BC");
    cout<<"**************************************************************\n";
    cout<<"*              Welcome to RMTS Bus service                   *"<<endl;
    cout<<"*Press Enter 1 to choose Bus Stop to go to Marwadi University*"<<endl;
    cout<<"**************************************************************\n";
    int temp;
    cin>>temp;
    bus x;
    here:
    x.stopdisplay();
    
    x.searchbus();
    int choice;
    cout<<"Enter 1 to Check timings of another Stop :"<<endl;
    cout<<"Enter 0 to EXIT"<<endl;
    cout<<"Choice:-";
    cin>>choice;
    
    if(choice)
    goto here;
    else 
    return 0;
}
