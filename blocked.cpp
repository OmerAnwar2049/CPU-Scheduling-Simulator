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
#include "Heap_Blocked.h"
using namespace std;

      pthread_t Input;

      pthread_t Output;

      pthread_t Printer;

      pthread_mutex_t lockI;
     

     int watch=0;  

    
    ///TO control the threads
    int Input_T = 0;
    int Output_T = 0;
    int Printer_T = 0;

    int count=0;



     // THIS IS THE A STRUCT AND ITS OBJECT WILL PASS TO THE THREADS AS A VOID POINTER
     // 1.Three different struct will be passed with their respective Heaps(based on IO time)
     // 2.These structs will have all the pointers requried for ITC.
 
  struct Blc
      {
          PriorityQueue  Q;
          int blocked_ready1 ;
          int running_blocked0_I;
          int running_blocked0_O;
          int running_blocked0_P;

            Blc(int a,int b,int c,int d)
            {      
               blocked_ready1 = a;
               running_blocked0_I = b;
               running_blocked0_O = c;
               running_blocked0_P = d;
            }
      };



  void* IN(void* object)
  {
    Blc *O = (Blc*)object;

     while(1)
    {
     //cout<<"\nThis is input thread\n";  

     Input_T=0;

     Node temp;

      srand(time(0));

         O->Q.I_WT(); //reducing the IO time

     if( (O->Q.getFront())!= NULL)
     {
          while((O->Q.getFront()->IO == 0))
          {
               Node temp2(O->Q.getFront());
               O->Q.dequeue();

               pthread_mutex_lock(&lockI);
               write(O->blocked_ready1,&temp2,sizeof(temp2));
               pthread_mutex_unlock(&lockI);

               if(O->Q.getFront() == NULL)
               break;
          }

     }
     int check = read(O->running_blocked0_I,&temp,sizeof(temp));
     if(check!= (-1))
     {
          //int random = (rand() % (25 - 15 + 25) + 15);
          int random = (rand() % (2 - 1 + 2) + 2);
          temp.IO = random;
          O->Q.enqueue(temp);
     }

 

     count++;

     while(Input_T == 0);

     
    }

  }//end


    void* OUT(void* object)
  {
    Blc *O = (Blc*)object;

      while(1)
    {
     //cout<<"\nThis is Output thread\n";  

     Output_T=0;

     Node temp;

      srand(time(0));

      O->Q.I_WT(); //reducing the IO time

    

     if( (O->Q.getFront())!= NULL)
     {
          while((O->Q.getFront()->IO == 0))
          {
               Node temp2(O->Q.getFront());
               O->Q.dequeue();
               pthread_mutex_lock(&lockI);
               write(O->blocked_ready1,&temp2,sizeof(temp2));
               pthread_mutex_unlock(&lockI);

               if(O->Q.getFront() == NULL)
               break;
          }

     }
     int check = read(O->running_blocked0_O,&temp,sizeof(temp));
     if(check!= (-1))
     {
          //int random = (rand() % (25 - 15 + 25) + 15);
          int random = (rand() % (2 - 1 + 2) + 2);
          temp.IO = random;
          O->Q.enqueue(temp);
     }
     

     

     count++;

     while(Output_T == 0);

     
    }

  }//end


  void* PRINT(void* object)
  {
    Blc *O = (Blc*)object;

       while(1)
    {
     //cout<<"\nThis is Printer thread\n";  

     Printer_T=0;

     Node temp;

      srand(time(0));

     O->Q.I_WT(); //reducing the IO time

     if( (O->Q.getFront())!= NULL)
     {
          while((O->Q.getFront()->IO == 0))
          {
               Node temp2(O->Q.getFront());
               O->Q.dequeue();

               pthread_mutex_lock(&lockI);
               write(O->blocked_ready1,&temp2,sizeof(temp2));
               pthread_mutex_unlock(&lockI);

               if(O->Q.getFront() == NULL)
               break;
          }

     }
     int check = read(O->running_blocked0_P,&temp,sizeof(temp));
     if(check!= (-1))
     {
          //int random = (rand() % (25 - 15 + 25) + 15);
          int random = (rand() % (2 - 1 + 2) + 2);
          temp.IO = random;
          O->Q.enqueue(temp);
     }

     

     count++;

     while(Printer_T == 0);

     
    }

  }//end


int main(int argc,char* argv[])
{

      int blocked_ready1 = atoi(argv[1]);
      int running_blocked0_I = atoi(argv[2]);
      int main_blocked0 = atoi(argv[3]);
      int blocked_main1 = atoi(argv[4]);
      int running_blocked0_O = atoi(argv[5]);
      int running_blocked0_P = atoi(argv[6]);
         
      int clock=0;

      if (pthread_mutex_init(&lockI, NULL) != 0) 
      { 
        cout<<"\n mutex init has failed\n"; 
       } 

  

       //CREATING THREE DIFF OBJECTS FOR THREE DIFFERENT THREADS
       Blc Venus(blocked_ready1,running_blocked0_I,running_blocked0_O,running_blocked0_P);
       Blc Artemis(blocked_ready1,running_blocked0_I,running_blocked0_O,running_blocked0_P);
       Blc Apollo(blocked_ready1,running_blocked0_I,running_blocked0_O,running_blocked0_P);

       int situation=0;


        char message[6] ={'R','E','A','D','Y','\0'};   
        char M[6];
        write(blocked_main1,message,sizeof(message));

        cout<<"Blocked Proc waiting for signal\n";
        read(main_blocked0,M,sizeof(M));

      pthread_create(&Input,NULL,IN,&Venus);
      pthread_create(&Output,NULL,OUT,&Artemis);
      pthread_create(&Printer,NULL,PRINT,&Apollo);



    while(1)
       {

             while(count!=3);
             count=0;

             write(blocked_main1,message,sizeof(message));
             read(main_blocked0,&situation,sizeof(situation));
             
             if(situation == 2)
             break;


            Input_T=1;
            Output_T=1;
            Printer_T=1;

            sleep(1);
            clock++;



       }


	
	
        pthread_exit(NULL);;
}




