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
#include "Heap_New.h"
using namespace std;


//Getline function for file reading
string getline(char temp[],int* index)
    {
    string check;
    for(;temp[*index] != '\n';(*index)++)
    {
        check += temp[*index];
    }
    (*index) ++;
    return check;
    }


int main(int argc,char* argv[])
{


        //storing the pipe descriptors
        int new_ready1 = atoi(argv[1]);
        int main_new0 = atoi(argv[2]);
        int new_main1 = atoi(argv[3]);
        

        PriorityQueue zeus;

        int clock=0;
     

        char buffer[10000]; //for storage of all characters form file

        int fd = open("processes.txt",O_RDONLY);
        int rd;

            while ((rd = read(fd, buffer, sizeof(buffer)-1)) != 0) /* read one less, to have a spare char available for the `0`-terminator. */
            {
            buffer[rd] = '\0';//putting null character in end
            
            }
        close(fd);

        //NOW BUFFER WILL STORE ALL THE PROC INFO
       

        int index = 0;

        int quantum = 0;
        string TYPE = getline(buffer,&index); //this will remain constant in all enqueues

        int s = TYPE.length();
        char typee[s+1];
        strcpy(typee,TYPE.c_str());

        write(new_main1,typee,sizeof(typee));///sending the name back to main for its insertion in other processes
        
        //Getting quantum in case of RR
        if(TYPE == "RR")
        {
            string q= getline(buffer,&index);
            quantum = stoi(q);
            cout<<quantum<<endl;
        }

        
        //ADDING ALL PROCESSES TO THE QUEUE
        while(buffer[index] != '\0')
        {
            string N = getline(buffer,&index);
            string A = getline(buffer,&index);
            string B = getline(buffer,&index);

            int Arr = stoi(A);
            int Bur = stoi(B);

            int n = N.length();
            char namee[n+1];
            strcpy(namee,N.c_str());

            
            zeus.enqueue(typee,namee,Arr,Bur,quantum);
        }  
    
        int sizee;
        read(main_new0,&sizee,sizeof(sizee));
        sizee = zeus.size;
        write(new_main1,&sizee,sizeof(sizee));
       

    int situation=0;


    //Sending ready message to main proc
    char message[6] ={'R','E','A','D','Y','\0'};   
    char M[6];
    write(new_main1,message,sizeof(message));
   
    cout<<"New Proc waiting for signal\n";
    read(main_new0,M,sizeof(M));
    


     while(1)
        {
        

          //SENDING PROCS TO NEW PROCESS ON THEIR ARRIVAL TIMES
          if((zeus.getFront()!=NULL))
          {
            while(zeus.getFront()->Arrival_T == clock)
             {           
                            

                Node sent(zeus.getFront());   
                 
                zeus.dequeue();     
                
                cout<<"Sending proc "<<sent.Name<<" to the ready process"<<endl;
                write(new_ready1,&sent,sizeof(sent));

                if(zeus.getFront() == NULL)
                break;
                 
            }  //loop end
          }

             write(new_main1,message,sizeof(message));
             read(main_new0,&situation,sizeof(situation));
             
             if(situation == 2)
             break;
            
            sleep(1);
            clock++;
        }
        return 0;
}


