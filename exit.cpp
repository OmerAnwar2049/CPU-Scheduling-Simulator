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
using namespace std;

int main(int argc,char* argv[])
{


        int running_exit0 = atoi(argv[1]);
        int main_exit0 = atoi(argv[2]);
        int exit_main1 = atoi(argv[3]);
        int size = atoi(argv[4]);
        int DOOM_1 = atoi(argv[5]);
        string schedule(argv[6]);
       
       cout<<"\nTHIS IS THE size "<<size<<"!"<<endl;

       int Total_TAT = 0;
       int Total_Wait = 0;
       int Total_Burst = 0;

        int clock=0;

        Node temp;

        Queue demo; 

        int count = 0;

        int situation = 0;


        
        string nline = "\n";
        string space = "     |     ";
        string line = "--------------------------------------------------------------|";
 
        string a = "                                     OMER'S SCHEDULING SYSTEM (WORKS RELIABLY SOMETIMES )\n\n";
        string b = "|| The Algorithm Implemented : ";
        string c = "\\ Name    | Arrival  | Burst     |Turnaround |  Waiting Time | \n";

        string d = "\\ Avg Turnaround   | Avg Waiting Time  | Throughput |\n";


        int fd = open("processes_stats.txt", O_WRONLY | O_TRUNC);
        int fd2 = open("processes_Avg.txt", O_WRONLY | O_TRUNC);


    

        //IN THE PROCESSES_STATS FILE
         write(fd,a.c_str(),strlen(a.c_str()));
         write(fd,b.c_str(),strlen(b.c_str())); 
         write(fd,schedule.c_str(),strlen(schedule.c_str()));
         write(fd,nline.c_str(),strlen(nline.c_str())); 
         write(fd,nline.c_str(),strlen(nline.c_str())); 

         write(fd,c.c_str(),strlen(c.c_str()));
         write(fd,line.c_str(),strlen(line.c_str())); 
         write(fd,nline.c_str(),strlen(nline.c_str())); 


         //IN THE PROCESSES_AVG FILE


              write(fd2,nline.c_str(),strlen(nline.c_str()));
              write(fd2,nline.c_str(),strlen(nline.c_str()));
              write(fd2,d.c_str(),strlen(d.c_str()));
              write(fd2,line.c_str(),strlen(line.c_str())); 
              write(fd2,nline.c_str(),strlen(nline.c_str())); 

       
        char message[6] ={'R','E','A','D','Y','\0'};   
        char M[6];
        write(exit_main1,message,sizeof(message));

        cout<<"Exit Proc waiting for signal\n";
        read(main_exit0,M,sizeof(M));


        //SEND NEW PROCESSES ONLY WHEN CLOCK IS EQUAL TO THEIR ARRIVAL TIME
      //sleep(2);
     while(1)
       {


            int t = read(running_exit0,&temp,sizeof(temp));


          
            if(t != (-1))
            {
              string N(temp.Name);
              count++;
              temp.TAT = temp.A_IN_R - temp.Arrival_T;

              Total_TAT += temp.TAT;
              Total_Wait += temp.Waitng_time;
              Total_Burst += temp.Original_Burst;

              string Arrival = to_string(temp.Arrival_T);
              string Burst = to_string(temp.Original_Burst);
              string TAT = to_string(temp.TAT);
              string W_T = to_string(temp.Waitng_time);

              write(fd,N.c_str(),strlen(N.c_str())); 
              write(fd,space.c_str(),strlen(space.c_str())); 
              write(fd,Arrival.c_str(),strlen(Arrival.c_str())); 
              write(fd,space.c_str(),strlen(space.c_str()));
              write(fd,Burst.c_str(),strlen(Burst.c_str())); 
              write(fd,space.c_str(),strlen(space.c_str()));
              write(fd,TAT.c_str(),strlen(TAT.c_str())); 
              write(fd,space.c_str(),strlen(space.c_str()));
              write(fd,W_T.c_str(),strlen(W_T.c_str())); 
              write(fd,space.c_str(),strlen(space.c_str()));
              write(fd,nline.c_str(),strlen(nline.c_str())); 
              write(fd,line.c_str(),strlen(line.c_str())); 
              write(fd,nline.c_str(),strlen(nline.c_str())); 
              demo.enqueue(temp);
            }
        
            


          if(clock!=0)
          {
             if( (clock%30) == 0)
            {
              float Avg_TAT = Total_TAT/count;
              float Avg_Wait = Total_Wait/count;
              float Through = Total_Burst/count;

              string T = to_string(Avg_TAT);
              string B = to_string(Avg_Wait);
              string Thru = to_string(Through);


              write(fd2,T.c_str(),strlen(T.c_str()));
              write(fd2,space.c_str(),strlen(space.c_str()));

              write(fd2,B.c_str(),strlen(B.c_str()));
              write(fd2,space.c_str(),strlen(space.c_str()));

              write(fd2,Thru.c_str(),strlen(Thru.c_str()));
              write(fd2,space.c_str(),strlen(space.c_str()));

              write(fd2,nline.c_str(),strlen(nline.c_str()));
              write(fd2,line.c_str(),strlen(line.c_str())); 
              write(fd2,nline.c_str(),strlen(nline.c_str()));

 

            }
          }



            if(count == size)
            {
            cout<<"\n\nDOOM CLOCK ACTIVATED\n";
            int doom = 2;
            write(DOOM_1,&doom,sizeof(doom));
            break;
            }

             //cout<<count<<endl;
             write(exit_main1,message,sizeof(message));
             read(main_exit0,&situation,sizeof(situation));
             
             if(situation == 2)
             break;



            sleep(1);
            clock++;      

       }


              float Avg_TAT = Total_TAT/size;
              float Avg_Wait = Total_Wait/size;
              float Through = Total_Burst/size;

              string T = to_string(Avg_TAT);
              string B = to_string(Avg_Wait);
              string Thru = to_string(Through);

              write(fd2,T.c_str(),strlen(T.c_str()));
              write(fd2,space.c_str(),strlen(space.c_str()));

              write(fd2,B.c_str(),strlen(B.c_str()));
              write(fd2,space.c_str(),strlen(space.c_str()));

              write(fd2,Thru.c_str(),strlen(Thru.c_str()));
              write(fd2,space.c_str(),strlen(space.c_str()));

              write(fd2,nline.c_str(),strlen(nline.c_str()));
              write(fd2,line.c_str(),strlen(line.c_str())); 
              write(fd2,nline.c_str(),strlen(nline.c_str()));



  
      cout<<"THE FINAL OUTPUT OF ALGO >> "<<schedule<<endl;

      cout<<"Name   Burst   Waiting_Time   Turnaround\n";

      demo.Print();
   
       close(fd);
       close(fd2);
	
        return 0;
}




