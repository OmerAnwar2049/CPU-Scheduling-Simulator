

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
#include "Queue.h"
#include "Heap_Ready.h"
using namespace std;


      pthread_t NewCheck;

      pthread_t BlockedCheck;

      pthread_t RunningCheck;

      pthread_t PreRunningCheck;

      pthread_mutex_t lock1;
      pthread_mutex_t lock2;
      pthread_mutex_t lock3;

      int count=0;

      int watch=0;   

      //thread check variables so that threads all report to the main thread
      int New_T=0;
      int Running_T=0;
      int Blocked_T=0;
      int Pre_Running_T=0;

      // To control the running thread
      int count2=0;

      int count3=0;

      bool New_Proc = false;
      bool Block_Proc = false;




      struct Info
      {
            Queue Q;
            int new_ready0;
            int ready_running1;
            int running_ready0 ;
            int blocked_ready0 ;
            int running_ready0_S;
            int Return_Pipe1;

            Info(int a,int b,int c,int d,int e,int f)
            {
            
            new_ready0 = a;
            ready_running1 = b;
            running_ready0  = c;
            blocked_ready0  = d;
            running_ready0_S = e;
            Return_Pipe1 = f;


            }
      };


      struct SJF
      {
            PriorityQueue Q;
            int new_ready0;
            int ready_running1;
            int running_ready0 ;
            int blocked_ready0 ;
            int running_ready0_S;
            int Return_Pipe1;

            SJF(int a,int b,int c,int d,int e,int f)
            {
            
            new_ready0 = a;
            ready_running1 = b;
            running_ready0  = c;
            blocked_ready0  = d;
            running_ready0_S = e;
            Return_Pipe1 = f;

            }
      };




////THREAD FUNCTIONS FCFS
void* NewMonitorFCFS(void* object)
  {      
    Info *O = (Info*)object;
    while(1)
    {
    //cout<<"This is new thread\n";

     New_T = 0;

          Node temp;
          int repeat = read(O->new_ready0,&temp,sizeof(temp));         
          while(repeat != (-1))
          {             
          pthread_mutex_lock(&lock1);
          O->Q.enqueue(temp);
          pthread_mutex_unlock(&lock1);
            
          repeat = read(O->new_ready0,&temp,sizeof(temp));
          }     

     count++;
     count2++;

     while(New_T == 0);

     
    }

  }//end

void* RunningMonitorFCFS(void* object)
  {
    Info *O = (Info*)object;
    
    int check;
 

     while(1)
    {


    while(count2 != 2);
    count2=0;


    Running_T = 0;
    //cout<<"\nThis is Running thread\n";
   
    int check2 = read(O->running_ready0,&check,sizeof(check));
    if(check == 1)
    {
      
      if(!O->Q.isEmpty())
      {
      cout<<"Sending to running proc\n"<<endl;//<<O->Q.getFront()->Name<<endl;     
       Node temp(O->Q.getFront());
       O->Q.dequeue();
       write(O->ready_running1,&temp,sizeof(temp));
       
      }

    }
    check=0;
    
    O->Q.I_WT();

     count++;
    
      while(Running_T == 0);

     
    }
  }//end

  void* BlockedMonitorFCFS(void* object)
  {
    Info *O = (Info*)object;

    Node temp;

     while(1)
    {
      Blocked_T=0;
    //cout<<"This is Blocked thread\n";

for(int i=0;i<2;i++)
{
    int check = read(O->blocked_ready0,&temp,sizeof(temp));
    while(check != (-1))
    {
      pthread_mutex_lock(&lock1);
      O->Q.enqueue(temp);
      pthread_mutex_unlock(&lock1);     
      check = read(O->blocked_ready0,&temp,sizeof(temp));
    }
}

    count++;
    count2++;
    while(Blocked_T == 0);
    
    }
  }//end
/////////////////



////THREAD FUNCTIONS SJF
void* NewMonitorSJF(void* object)
  {      
    SJF *O = (SJF*)object;
    while(1)
    {
    //cout<<"This is new thread SJF\n";

     New_T = 0;

          Node temp;
          int repeat = read(O->new_ready0,&temp,sizeof(temp));         
          while(repeat != (-1))
          {             
          pthread_mutex_lock(&lock1);
          O->Q.enqueue(temp);
          pthread_mutex_unlock(&lock1);
            
          repeat = read(O->new_ready0,&temp,sizeof(temp));
          }     

     count++;
     count2++;

     while(New_T == 0);

    }

  }//end

void* RunningMonitorSJF(void* object)
  {
    SJF *O = (SJF*)object;
    
    int check;


     while(1)
    {

    while(count2 != 2);
    count2=0;


    Running_T = 0;
    //cout<<"\nThis is Running thread SJF\n";
   
    int check2 = read(O->running_ready0,&check,sizeof(check));
    if(check == 1)
    {
      
      if(!O->Q.isEmpty())
      {
      cout<<"Sending to running proc\n"<<endl;//<<O->Q.getFront()->Name<<endl;     
       Node temp(O->Q.getFront());
       O->Q.dequeue();
       write(O->ready_running1,&temp,sizeof(temp));
       
      }

    }
    check=0;
    
    O->Q.I_WT();

     count++;
    
      while(Running_T == 0);

     
    }
  }//end

  void* BlockedMonitorSJF(void* object)
  {
    SJF *O = (SJF*)object;

    Node temp;

     while(1)
    {
      Blocked_T=0;
    //cout<<"This is Blocked thread SJF\n";

for(int i=0;i<2;i++)
{
    int check = read(O->blocked_ready0,&temp,sizeof(temp));
    while(check != (-1))
    {
      pthread_mutex_lock(&lock1);
      O->Q.enqueue(temp);
      pthread_mutex_unlock(&lock1);     
      check = read(O->blocked_ready0,&temp,sizeof(temp));
    }
}

    count++;
    count2++;
    while(Blocked_T == 0);
    
    }
  }//end
/////////////////





///////////RR  For this only the running thread will be changed as it should cater the changes of time slice

void* RunningMonitorRR(void* object)
  {

    Info *O = (Info*)object;
    
    int check;

     while(1)
    {

    while(count2 != 3);
    count2=0;


    Running_T = 0;
    //cout<<"\nThis is Running thread\n";
     
    int check2 = read(O->running_ready0,&check,sizeof(check));
    if(check == 1)
    {     
      if(!O->Q.isEmpty())
      {
       cout<<"Sending to running proc\n"<<endl;//<<O->Q.getFront()->Name<<endl;     
       Node temp(O->Q.getFront());
       O->Q.dequeue();
       write(O->ready_running1,&temp,sizeof(temp));
       
      }
    }///if (check==1)
   
   O->Q.I_WT();

    check=0;
     count++;
      while(Running_T == 0);

     
    }
  }//end

void* PreMonitorRR(void* object)
  {

    Info *O = (Info*)object;
    
    int check2=0;
    Node temp;
    
     while(1)
    {
    Pre_Running_T = 0;
    //cout<<"\nThis is Running thread\n";
   
    check2 = read(O->running_ready0_S,&temp,sizeof(temp));
    if(check2 != (-1))
    {         
      temp.Refresh();
      pthread_mutex_lock(&lock1);
      O->Q.enqueue(temp);
      pthread_mutex_unlock(&lock1); 
    }///if (check==1)

    check2=0;
    count2++;
     //count++;
      while(Pre_Running_T == 0);

     
    }
  }//end


  /////////////////////////////////////////////////////////////////////

///////////RR  For this only the running thread will be changed as it should cater the changes of time slice

void* NewMonitorSRTF(void* object)
  {      
    SJF *O = (SJF*)object;
    while(1)
    {
    //cout<<"This is new thread SJF\n";

     New_T = 0;

          Node temp;
          int repeat = read(O->new_ready0,&temp,sizeof(temp));         
          while(repeat != (-1))
          {                
          New_Proc = true;
          pthread_mutex_lock(&lock1);
          O->Q.enqueue(temp);
          pthread_mutex_unlock(&lock1);
            
          repeat = read(O->new_ready0,&temp,sizeof(temp));
          }     


     //count3++;
     count2++;
     count++;


     while(New_T == 0);

    }

  }//end


   void* BlockedMonitorSRTF(void* object)
  {
    SJF *O = (SJF*)object;

  
    Node temp;

     while(1)
    {
      Blocked_T=0;
    //cout<<"This is Blocked thread SJF\n";

    for(int i=0;i<2;i++)
    {
    int check = read(O->blocked_ready0,&temp,sizeof(temp));
    while(check != (-1))
    {
      Block_Proc = true;
      pthread_mutex_lock(&lock1);
      O->Q.enqueue(temp);
      pthread_mutex_unlock(&lock1);     
      check = read(O->blocked_ready0,&temp,sizeof(temp));
    }
}

    //count3++;
    count2++;
    count++;
    while(Blocked_T == 0);
    
    }
  }//end
/////////////////


void* RunningMonitorSRTF(void* object)
  {

     SJF *O = (SJF*)object;
    
    int check;

    int useless=6;

    int nothing = -5;

     while(1)
    {

      Node trial;
      int tru = read(O->running_ready0_S,&trial,sizeof(trial));   

      while(count2!= 2);
      count2=0;


    Running_T = 0;
    //cout<<"\nThis is Running thread\n";
     
    int check2 = read(O->running_ready0,&check,sizeof(check));
    if(check == 1)
    {     
      if(!O->Q.isEmpty())
      {
       cout<<"Sending to running proc\n"<<endl;
       Node temp(O->Q.getFront());
       O->Q.dequeue();
       write(O->ready_running1,&temp,sizeof(temp));
       
      }
    }///if (check==1)


    else
    {
       int positive=1;
        int negative=2;
      
      if(Block_Proc || New_Proc)
      {

      if(tru != -1)
      {
       

        if(O->Q.getFront()->Burst < trial.Burst)   
        {  
        write(O->Return_Pipe1,&positive,sizeof(positive));
        O->Q.enqueue(trial);
        }


        else
        write(O->Return_Pipe1,&negative,sizeof(negative));



      }//if tru
      }

      else
      write(O->Return_Pipe1,&negative,sizeof(negative));


    }

    Block_Proc = false;
    New_Proc = false;


    O->Q.I_WT();

    check=0;
     count++;
      while(Running_T == 0);
     
    }
  }//end


void* PreMonitorSRTF(void* object)
  {

     SJF *O = (SJF*)object;
    
    int check2=0;
    
    
     while(1)
    {


     // while(count3 != 2);//controlled by new thread
     // count3=0;
   
      Pre_Running_T = 0;
   
      check2=0;

int Big_Monitor = read(O->running_ready0_S,&check2,sizeof(check2));

  if(check2 == 9)
  {

    if(New_Proc || Block_Proc)
    {

      int B = O->Q.getFront()->Burst;
      int zeus;
      if(B!=0)
      {
      write(O->Return_Pipe1,&B,sizeof(B));
      read(O->running_ready0_S,&zeus,sizeof(zeus));
      if(zeus == 1)
      {
        Node temp;
        write(O->Return_Pipe1,&B,sizeof(B));   
        read(O->running_ready0_S,&temp,sizeof(temp));          
        
        pthread_mutex_lock(&lock1);
        O->Q.enqueue(temp);
        pthread_mutex_unlock(&lock1);
        
      }///if (check==1)
      }
    }
  }//if(check2 == 9)


      New_Proc = false;
      Block_Proc = false;


    
    check2=0;
    //count2++;
     //count++;
    while(Pre_Running_T == 0);//controlled by the main thread

     
    }



  }


  /////////////////////////////////////////////////////////////////////






int main(int argc,char* argv[])
{
      int new_ready0 = atoi(argv[1]);
      int ready_running1 = atoi(argv[2]);
      int running_ready0 = atoi(argv[3]);
      int blocked_ready0 = atoi(argv[4]);
      int main_ready0 = atoi(argv[5]);
      int ready_main1 = atoi(argv[6]);
      string schedule(argv[7]);
      int running_ready0_S = atoi(argv[8]);
      int Return_Pipe1 = atoi(argv[9]);
     
     if (pthread_mutex_init(&lock1, NULL) != 0) 
      { 
        cout<<"\n mutex init has failed\n"; 
       } 



      //Creating the objects which will be passed to the threads
      Info Pluto(new_ready0,ready_running1,running_ready0,blocked_ready0,running_ready0_S,Return_Pipe1);
      SJF Hades(new_ready0,ready_running1,running_ready0,blocked_ready0,running_ready0_S,Return_Pipe1);


      int situation=0;


          //FOR STARTING THE CLOCK
      char message[6] ={'R','E','A','D','Y','\0'}; 
      char M[6];
        
      write(ready_main1,message,sizeof(message));
      cout<<"Ready proc waiting for signal\n";
      read(main_ready0,M,sizeof(M));



      //THREAD CREATION BASED ON THE SCHEDULER CHOSEN

      if((schedule == "FCFS"))
      {
      pthread_create(&NewCheck,NULL,NewMonitorFCFS,&Pluto);
      pthread_create(&BlockedCheck,NULL,BlockedMonitorFCFS,&Pluto);
      pthread_create(&RunningCheck,NULL,RunningMonitorFCFS,&Pluto);
      }

      else if(schedule == "SJF")
      {
      pthread_create(&NewCheck,NULL,NewMonitorSJF,&Hades);
      pthread_create(&BlockedCheck,NULL,BlockedMonitorSJF,&Hades);
      pthread_create(&RunningCheck,NULL,RunningMonitorSJF,&Hades);
      }

      else if(schedule == "RR")
      {
      pthread_create(&NewCheck,NULL,NewMonitorFCFS,&Pluto);
      pthread_create(&BlockedCheck,NULL,BlockedMonitorFCFS,&Pluto);
      pthread_create(&RunningCheck,NULL,RunningMonitorRR,&Pluto);
      pthread_create(&PreRunningCheck,NULL,PreMonitorRR,&Pluto);
      }
    
      else if(schedule == "SRTF")
      {
      pthread_create(&NewCheck,NULL,NewMonitorSRTF,&Hades);
      pthread_create(&BlockedCheck,NULL,BlockedMonitorSRTF,&Hades);
      pthread_create(&RunningCheck,NULL,RunningMonitorSRTF,&Hades);
      
      }

       
     
     while(1)
       {
         
         //FOR CONTROLLING THE MAIN THREAD
         while(count!=3)
         {
         }
          count=0;


             write(ready_main1,message,sizeof(message));
             read(main_ready0,&situation,sizeof(situation));
             
             if(situation == 2)
             break;


             New_T=1;
             Blocked_T=1;
             Pre_Running_T=1;
             Running_T=1;

            sleep(1);
            watch++;

       }

        exit(1);
}



