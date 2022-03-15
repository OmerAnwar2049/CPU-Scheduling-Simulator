#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include <sstream>
#include "Node.h"
#include<time.h>
using namespace std;



int main(int argc,char* argv[])
{
      int ready_running0 = atoi(argv[1]);
      int running_ready1 = atoi(argv[2]);
      int running_exit1 = atoi(argv[4]);
      int main_running0 = atoi(argv[5]);
      int running_main1 = atoi(argv[6]);
      int running_blocked1_I = atoi(argv[3]);
      int running_blocked1_O = atoi(argv[7]);
      int running_blocked1_P = atoi(argv[8]);
      string schedule(argv[9]);
      int running_ready1_S = atoi(argv[10]);
      int Return_Pipe0 = atoi(argv[11]);

      int clock=0;

       int number = -1;
       int IO_type;

      int empty = 0;

      int approval = 1;
      int approval2 = 2;

      Node temp;
      
      bool IO_Sent=false;

      srand(time(0));


      int situation=0;






                 int No = 5;
      
               bool Pre = false;

      char message[6] ={'R','E','A','D','Y','\0'};   
      char M[6];
      write(running_main1,message,sizeof(message));

      cout<<"Running Proc waiting for signal\n";
      read(main_running0,M,sizeof(M));

        
    while(1)
       {
        cout<<"This in running process,time is->"<<clock<<endl;

        IO_Sent=false;

        Pre = false;

        int Compare = -5; 



          if((schedule == "FCFS")  || (schedule == "SJF"))
          {

            if(empty==0)
            {            

                
                write(running_ready1,&approval,sizeof(approval));
                
                int r = read(ready_running0,&temp,sizeof(temp)); 

                if(r != (-1))   
                {         
                empty =1;
               
                
            if(clock%5 == 0)
            {

                  number = (rand() % (1 - 0 + 1) + 0);   
                              
                  //cout<<"\nThe random number generated is "<<number<<endl;
                   
                  if(number == 0)
                  {
                  cout<<"\nSending to Blocked proc\n";
                  IO_type = (rand() % (3- 1 + 3) + 1);
                  temp.IO_type = IO_type;


                  if(IO_type == 1)
                  write(running_blocked1_I,&temp,sizeof(temp));

                  else if(IO_type == 2)
                  write(running_blocked1_O,&temp,sizeof(temp));

                  else 
                  write(running_blocked1_P,&temp,sizeof(temp));


                  empty=0;
                  IO_Sent = true;
                  }//if(number ==0)

                  else
                  {
                    IO_Sent = false;
                  }
                  

            }//if(clock%3 ==0)


            if(IO_Sent == false)
               {
                if(temp.Burst!=0)
                  {
                  cout<<"Reducing Burst of"<<temp.Name<<endl;
                  temp.Burst -= 1;
                  }
                if(temp.Burst == 0)
                  {
                  cout<<temp.Name<<" process has finished !"<<endl;
                  temp.A_IN_R = clock;
                  write(running_exit1,&temp,sizeof(temp));
                  empty = 0;                   
                  }
                }//else of clock         


                }//if r!= -1  


                else if(r == (-1))
                cout<<"\nRunning process will be empty\n";


            }//if (empty==0)

            else if(empty == 1)
            {


            if(clock%5 == 0)
                {

                  number = (rand() % (1 - 0 + 1) + 0); 
                  //number=0;                
                  //cout<<"\nThe random number generated is "<<number<<endl;
                   
                 if(number == 0)
                  {
                  cout<<"\nSending to Blocked proc\n";
                  IO_type = (rand() % (3- 1 + 3) + 1);
                  temp.IO_type = IO_type;

                  if(IO_type == 1)
                  write(running_blocked1_I,&temp,sizeof(temp));

                  else if(IO_type == 2)
                  write(running_blocked1_O,&temp,sizeof(temp));

                  else
                  write(running_blocked1_P,&temp,sizeof(temp));


                  empty=0;
                  IO_Sent = true;
                  }//if(number ==0)

                   else
                  {
                    IO_Sent = false;
                  }

            }//if(clock%3 ==0)


            if(IO_Sent==false)
            {
                  if(temp.Burst!=0)
                  {
                  cout<<"Reducing Burst of"<<temp.Name<<endl;
                  temp.Burst -= 1;
                  }
                  if(temp.Burst == 0)
                  {
                    cout<<temp.Name<<" process has finished !"<<endl;
                    temp.A_IN_R = clock;
                    write(running_exit1,&temp,sizeof(temp));
                    empty = 0;                   
                  }

            }///clock else
                  
                                
            }//else if(empty==1)


          }//Non-Preemptive end







         else if(schedule == "RR")
         {

            if(empty==0)
            {            
              
                write(running_ready1,&approval,sizeof(approval));
                
                int r = read(ready_running0,&temp,sizeof(temp)); 

                if(r != (-1))   
                {         
                empty =1;
               
                
                if(clock%5 == 0)
                {

                  number = (rand() % (1 - 0 + 1) + 0);   
                              
                  //cout<<"\nThe random number generated is "<<number<<endl;
                   
                  if(number == 0)
                  {
                  cout<<"\nSending to Blocked proc\n";
                  IO_type = (rand() % (3- 1 + 3) + 1);
                  temp.IO_type = IO_type;


                  if(IO_type == 1)
                  write(running_blocked1_I,&temp,sizeof(temp));

                  else if(IO_type == 2)
                  write(running_blocked1_O,&temp,sizeof(temp));

                  else 
                  write(running_blocked1_P,&temp,sizeof(temp));


                  empty=0;
                  IO_Sent = true;
                  }//if(number ==0)

                  else
                  {
                    IO_Sent = false;
                  }
                  

            }//if(clock%3 ==0)


            if(IO_Sent == false)
               {

                if(temp.quantum!= 0)
                {
                  temp.quantum-=1;
                }

                if(temp.Burst!=0)
                  {
                  cout<<"Reducing Burst of"<<temp.Name<<endl;
                  temp.Burst -= 1;
                  }
                if(temp.Burst == 0)
                  {
                 cout<<temp.Name<<" process has finished !"<<endl;
                  temp.A_IN_R = clock;
                  write(running_exit1,&temp,sizeof(temp));
                  empty = 0;                   
                  }
                }//else of clock         


                }//if r!= -1  


                else if(r == (-1))
                {
                cout<<"\nRunning process will be empty\n";
                empty=0;
                }

            }//if (empty==0)


            else if(empty == 1)
            {

              if(temp.quantum == 0)
              {                       

                write(running_ready1_S,&temp,sizeof(temp));
                               
                write(running_ready1,&approval,sizeof(approval));
                
                int r = read(ready_running0,&temp,sizeof(temp)); 

                if(r != (-1))   
                {         
                empty =1;
               
                
                if(clock%5 == 0)
                {

                  number = (rand() % (1 - 0 + 1) + 0);   
                              
                 // cout<<"\nThe random number generated is "<<number<<endl;
                   
                  if(number == 0)
                  {
                  cout<<"\nSending to Blocked proc\n";
                  IO_type = (rand() % (3- 1 + 3) + 1);
                  temp.IO_type = IO_type;


                  if(IO_type == 1)
                  write(running_blocked1_I,&temp,sizeof(temp));

                  else if(IO_type == 2)
                  write(running_blocked1_O,&temp,sizeof(temp));

                  else 
                  write(running_blocked1_P,&temp,sizeof(temp));


                  empty=0;
                  IO_Sent = true;
                  }//if(number ==0)

                  else
                  {
                    IO_Sent = false;
                  }
                  

            }//if(clock%3 ==0)


            if(IO_Sent == false)
               {

                if(temp.quantum!= 0)
                {
                  temp.quantum-=1;
                }

                if(temp.Burst!=0)
                  {
                  cout<<"Reducing Burst of"<<temp.Name<<endl;
                  temp.Burst -= 1;
                  }
                if(temp.Burst == 0)
                  {
                  cout<<temp.Name<<" process has finished !"<<endl;
                  temp.A_IN_R = clock;
                  write(running_exit1,&temp,sizeof(temp));
                  empty = 0;                   
                  }
                }//else of clock         


                }//if r!= -1  


                else if(r == (-1))
                {
                cout<<"\nRunning process will be empty\n";
                empty=0;
                }
                
              }//if quantum=0

            


            else
            {

            if(clock%5 == 0)
                {

                  number = (rand() % (1 - 0 + 1) + 0); 
                  //number=0;                
                  //cout<<"\nThe random number generated is "<<number<<endl;
                   
                 if(number == 0)
                  {
                  cout<<"\nSending to Blocked proc\n";
                  IO_type = (rand() % (3- 1 + 3) + 1);
                  temp.IO_type = IO_type;

                  if(IO_type == 1)
                  write(running_blocked1_I,&temp,sizeof(temp));

                  else if(IO_type == 2)
                  write(running_blocked1_O,&temp,sizeof(temp));

                  else
                  write(running_blocked1_P,&temp,sizeof(temp));


                  empty=0;
                  IO_Sent = true;
                  }//if(number ==0)

                   else
                  {
                    IO_Sent = false;
                  }

            }//if(clock%3 ==0)


             if(IO_Sent==false)
             {

                  if(temp.quantum!= 0)
                  {
                  temp.quantum-=1;
                  }

                  if(temp.Burst!=0)
                  {
                  cout<<"Reducing Burst of"<<temp.Name<<endl;
                  temp.Burst -= 1;
                  }
                  if(temp.Burst == 0)
                  {
                    cout<<temp.Name<<" process has finished !"<<endl;
                    temp.A_IN_R = clock;
                    write(running_exit1,&temp,sizeof(temp));
                    empty = 0;                   
                  }

              }///clock else
                 


             }//if quantu != 0     
                                
            }//else if(empty==1)



         }///RR end



 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////       
       
         else if(schedule == "SRTF")
         {

            if(empty==0)
            {            
                
              
                write(running_ready1,&approval,sizeof(approval));
                
                int r = read(ready_running0,&temp,sizeof(temp)); 

                if(r != (-1))   
                {         
                empty =1;
                
                
                if(clock%5 == 0)
                {
                  number = (rand() % (1 - 0 + 1) + 0);   
                              
                  //cout<<"\nThe random number generated is "<<number<<endl;
                   
                  if(number == 0)
                  {
                  cout<<"\nSending to Blocked proc\n";
                  IO_type = (rand() % (3- 1 + 3) + 1);
                  temp.IO_type = IO_type;


                  if(IO_type == 1)
                  write(running_blocked1_I,&temp,sizeof(temp));

                  else if(IO_type == 2)
                  write(running_blocked1_O,&temp,sizeof(temp));

                  else 
                  write(running_blocked1_P,&temp,sizeof(temp));


                  empty=0;
                  IO_Sent = true;
                  }//if(number ==0)

                  else
                  {
                    IO_Sent = false;
                  }
                  

            }//if(clock%3 ==0)


            if(IO_Sent == false)
               {


                if(temp.Burst!=0)
                  {
                  cout<<"Reducing Burst of"<<temp.Name<<endl;
                  temp.Burst -= 1;
                  }
                if(temp.Burst == 0)
                  {
                  cout<<temp.Name<<" process has finished !"<<endl;
                  temp.A_IN_R = clock;
                  write(running_exit1,&temp,sizeof(temp));
                  empty = 0;                   
                  }
                }//else of clock         


                }//if r!= -1  


                else if(r == (-1))
                {
                cout<<"\nRunning process will be empty\n";
                empty=0;
                }

            }//if (empty==0)


            else if(empty == 1)
            {

              write(running_ready1_S,&temp,sizeof(temp));
              int Apollo = read(Return_Pipe0,&Compare,sizeof(Compare));

              //if(Apollo != (-1))
              //{
                if(Compare == 1)
                {
                  
                           
                cout<<"\nRunning process will be empty\n";
                empty=0;
                Pre = true;

               
               }//if apollo != -1   

              //}                  

       
            if(!Pre)
            {

            if(clock%5 == 0)
                {

                  number = (rand() % (1 - 0 + 1) + 0); 
                  //number=0;                
                  cout<<"\nThe random number generated is "<<number<<endl;
                   
                 if(number == 0)
                  {
                  cout<<"\nSending to Blocked proc\n";
                  IO_type = (rand() % (3- 1 + 3) + 1);
                  temp.IO_type = IO_type;

                  if(IO_type == 1)
                  write(running_blocked1_I,&temp,sizeof(temp));

                  else if(IO_type == 2)
                  write(running_blocked1_O,&temp,sizeof(temp));

                  else
                  write(running_blocked1_P,&temp,sizeof(temp));


                  empty=0;
                  IO_Sent = true;
                  }//if(number ==0)

                   else
                  {
                    IO_Sent = false;
                  }

            }//if(clock%3 ==0)


             if(IO_Sent==false)
             {

                  if(temp.Burst!=0)
                  {
                  cout<<"Reducing Burst of"<<temp.Name<<endl;
                  temp.Burst -= 1;
                  }
                  if(temp.Burst == 0)
                  {
                    cout<<endl<<temp.Name<<" process has finished !"<<endl;
                    temp.A_IN_R = clock;
                    write(running_exit1,&temp,sizeof(temp));
                    empty = 0;                   
                  }

              }///clock else
                 


             }//if quantu != 0     
                                
            }//else if(empty==1)



         }///SRTF end


          



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

             write(running_main1,message,sizeof(message));
             read(main_running0,&situation,sizeof(situation));
             
             if(situation == 2)
             break;

        sleep(1);
        clock++;
       }


	
	
        return 0;
}




/* else if((clock%3) == 0)
                  {
                      number = (rand() % (1 - 0 + 1) + 0);
                      cout<<"\nThe random number generated is "<<number<<endl;
                   
                      if(number == 0)
                      {
                      cout<<"\nSending to Blocked proc\n";
                      IO_type = (rand() % (3- 1 + 3) + 1);
                      temp.IO_type = IO_type;

                      if(IO_type == 1)
                      write(running_blocked1_I,&temp,sizeof(temp));

                      else if(IO_type == 2)
                      write(running_blocked1_O,&temp,sizeof(temp));

                      if(IO_type == 3)
                      write(running_blocked1_P,&temp,sizeof(temp));

                      empty = 0;
                      }
                  
                  }*/