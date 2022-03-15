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
#include <queue> 
using namespace std;


struct Node
{

Node*next;

char type[10];//this is their scheduling type
char Name[10];//name of process  
int Arrival_T;//in new process
int Burst;//decremented int the running process

int Waitng_time;//will be incremented in the ready process of all procs(thus create a function in queue)
int TAT;//calculate in exit process
int IO;//in blocked queue random number will be generated
int IO_type;//printer etc(blocked state)
int quantum;//in case of round robin
int Complete;
int A_IN_R;
int Original_Quantum;
int Original_Burst;



    Node()
    {
      type[0] ='\0';
      Name[0] = '\0';
      Arrival_T =0;
      Burst = 0;
      quantum = 0;

      Waitng_time = 0;
      TAT = 0;
      IO = 0;
      IO_type =-1;
      Complete=0;
       A_IN_R = 0;
     Original_Quantum = 0;

    }


    Node(char T[],char N[],int Arrival,int burst,int Q = 0)
    {	
      strncpy(type,T,strlen(T));
      strncpy(Name,N,strlen(N));
      Arrival_T = Arrival;
      Burst = burst;
      quantum = Q;

      Waitng_time = 0;
      TAT = 0;
      IO = 0;
      IO_type  = -1;
	Complete=0;
	A_IN_R = 0;
	Original_Quantum = Q;
	Original_Burst = burst;


    }

     Node(Node* &copy)
    {


      strncpy(type,copy->type,strlen(copy->type));
      strncpy(Name,copy->Name,strlen(copy->Name));
      
      Arrival_T = copy->Arrival_T;
      Burst = copy->Burst;
      quantum = copy->quantum;

      Waitng_time = copy->Waitng_time;
      TAT = copy->TAT;
      IO = copy->IO;
	Complete=copy->Complete;
	 A_IN_R = copy->A_IN_R;

      IO_type = copy->IO_type;
	Original_Quantum = copy->Original_Quantum;
	Original_Burst = copy->Original_Burst;

    }

   Node(Node &copy)
    {


      strncpy(type,copy.type,strlen(copy.type));
      strncpy(Name,copy.Name,strlen(copy.Name));
      
      Arrival_T = copy.Arrival_T;
      Burst = copy.Burst;
      quantum = copy.quantum;

      Waitng_time = copy.Waitng_time;
      TAT = copy.TAT;
      Complete=copy.Complete;
      A_IN_R = copy.A_IN_R;
      IO = copy.IO;
      IO_type = copy.IO_type;

      Original_Quantum = copy.Original_Quantum;
	Original_Burst = copy.Original_Burst;


    }

	void ReduceBurst()
	{
	this->Burst -=1;
	}

	void Refresh()
	{
	quantum = Original_Quantum;
	}


    void Display()
    {
        cout<<Name<<"       "<<Original_Burst<<"        "<<Waitng_time<<"        "<<TAT<<endl;
    }

};
