#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>
#include <sstream>
using namespace std;


int main() 
{ 

int NewtoReady[2],ReadytoRunning[2],RunningtoReady[2],RunningtoReady_S[2],Return_Pipe[2],BlockedtoReady[2],RunningtoBlocked_I[2],RunningtoBlocked_O[2],
RunningtoBlocked_P[2],RunningtoExit[2]; //will pass to states

int MaintoNew[2],MaintoReady[2], MaintoRunning[2], MaintoBlocked[2],MaintoExit[2] , DOOM_PIPE[2];

if((pipe(DOOM_PIPE) == -1) ||	(pipe(MaintoNew) == -1) || (pipe(MaintoReady) == -1) || (pipe(MaintoRunning) == -1)|| (pipe(MaintoBlocked) == -1)|| (pipe(MaintoExit) == -1))
cout<<"Pipes not created error";


if(	(pipe(Return_Pipe) == -1) || (pipe(NewtoReady) == -1) || (pipe(ReadytoRunning) == -1) || (pipe(RunningtoReady) == -1)|| (pipe(BlockedtoReady) == -1)|| (pipe(RunningtoBlocked_I) == -1) || 
(pipe(RunningtoBlocked_O) == -1)|| (pipe(RunningtoBlocked_P) == -1)|| 
(pipe(RunningtoExit) == -1)  )
cout<<"Pipes not created error";


if(pipe(RunningtoReady_S) == -1)
cout<<"Error\n";


if(fcntl(Return_Pipe[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";

if(fcntl(RunningtoReady_S[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";

if(fcntl(DOOM_PIPE[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";

if(fcntl(NewtoReady[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";

if(fcntl(RunningtoReady[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";

if(fcntl(ReadytoRunning[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";


if(fcntl(BlockedtoReady[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";

if(fcntl(RunningtoBlocked_I[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";
if(fcntl(RunningtoBlocked_O[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";
if(fcntl(RunningtoBlocked_P[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";

if(fcntl(RunningtoExit[0], F_SETFL, O_NONBLOCK) < 0)
cout<<"Error";


//MAKING DUPLICATES OF PIPE DESCRIPTORS

//FOR NEWTOREADY PIPE
int new_ready0 = dup(NewtoReady[0]);
int new_ready1 = dup(NewtoReady[1]);

//FOR READYTORUNNING PIPE
int ready_running0 = dup(ReadytoRunning[0]);
int ready_running1 = dup(ReadytoRunning[1]);


//FOR RUNNINGTOREADY PIPE
int running_ready0 = dup(RunningtoReady[0]);
int running_ready1 = dup(RunningtoReady[1]);

int running_ready0_S = dup(RunningtoReady_S[0]);
int running_ready1_S = dup(RunningtoReady_S[1]);


//FOR BLOCKEDTOREADY PIPE
int blocked_ready0 = dup(BlockedtoReady[0]);
int blocked_ready1 = dup(BlockedtoReady[1]);


//FOR RUNNINGTOBLOCKED PIPE
int running_blocked0_I = dup(RunningtoBlocked_I[0]);
int running_blocked1_I = dup(RunningtoBlocked_I[1]);

int running_blocked0_O = dup(RunningtoBlocked_O[0]);
int running_blocked1_O = dup(RunningtoBlocked_O[1]);

int running_blocked0_P = dup(RunningtoBlocked_P[0]);
int running_blocked1_P = dup(RunningtoBlocked_P[1]);


//FOR RUNNINGTOEXIT PIPE
int running_exit0 = dup(RunningtoExit[0]);
int running_exit1 = dup(RunningtoExit[1]);





/////////////////////////////////////////
//FOR MAINTONEW PIPE
int main_new0 = dup(MaintoNew[0]);
int main_new1 = dup(MaintoNew[1]);

//FOR MAINTOREADY PIPE
int main_ready0 = dup(MaintoReady[0]);
int main_ready1 = dup(MaintoReady[1]);


//FOR MAINTORUNNING PIPE
int main_running0 = dup(MaintoRunning[0]);
int main_running1 = dup(MaintoRunning[1]);


//FOR MAINTOBLOCKED PIPE
int main_blocked0 = dup(MaintoBlocked[0]);
int main_blocked1 = dup(MaintoBlocked[1]);


//FOR MAINTOEXIT PIPE
int main_exit0 = dup(MaintoExit[0]);
int main_exit1 = dup(MaintoExit[1]);



int NewToMain[2];


int ReadyToMain[2];


int RunningToMain[2];


int BlockedToMain[2];


int ExitToMain[2];



if(	pipe(NewToMain) == -1 || pipe(ReadyToMain) == -1 || pipe(RunningToMain) == -1|| pipe(BlockedToMain)== -1|| pipe(ExitToMain) == -1)
cout<<"Pipes not created error";




int pid1,pid2,pid3,pid4,pid5;


	pid1 = fork();
	
	if(pid1 == 0)
	{
		stringstream ss,b1,b2;
		ss<<new_ready1;
		string str1 = ss.str();
		b1<<main_new0;
		string a1 = b1.str();
		b2<<NewToMain[1];
		string a2 = b2.str();

		execl("./newstate","new",str1.c_str(),a1.c_str(),a2.c_str(),NULL);
	}

	else//parent
	{
		char typee[6];
		read(NewToMain[0],typee,sizeof(typee));
		string buffer(typee);
		cout<<"\n\nTHIS IS RECIEVED FOR THE NEW PROC "<<buffer<<"!"<<endl<<endl;
		
		int sizee =1;

		write(main_new1,&sizee,sizeof(sizee));

		read(NewToMain[0],&sizee,sizeof(sizee));
		

		pid2 = fork();

		if(pid2 == 0) 
		{
			//call ready execl
			stringstream b1,b2,b3,b4,b5,b6,b7,b8;
			b1<<new_ready0;
			string a1 = b1.str();
		
			b2<<ready_running1;
			string a2 = b2.str();
	
			b3<<running_ready0;
			string a3 = b3.str();
			
			b4<<blocked_ready0;
			string a4 = b4.str();

			b5<<main_ready0;
			string a5 = b5.str();
			
			b6<<ReadyToMain[1];
			string a6 = b6.str();

		 	b7<<running_ready0_S;
			string a7 = b7.str();

			b8<<Return_Pipe[1];
			string a8 = b8.str();


		execl("./readystate","ready",a1.c_str(),a2.c_str(),a3.c_str(),a4.c_str(),a5.c_str(),a6.c_str(),buffer.c_str(),a7.c_str(),a8.c_str(),NULL);

		}

		else///Parent
		{
			pid3 = fork();

			if(pid3 == 0)
			{
				//call execl for Running
		
			stringstream b1,b2,b3,b4,b5,b6,b7,b8,b9,b10;
			b1<<ready_running0;
			string a1 = b1.str();
		
			b2<<running_ready1;
			string a2 = b2.str();
	
			b3<<running_blocked1_I;
			string a3 = b3.str();
			
			b4<<running_exit1;
			string a4 = b4.str();

			b5<<main_running0;
			string a5 = b5.str();
			
			b6<<RunningToMain[1];
			string a6 = b6.str();

			b7<<running_blocked1_O;
			string a7 = b7.str();

			b8<<running_blocked1_P;
			string a8 = b8.str();

			b9<<running_ready1_S;
			string a9 = b9.str();

			b10<<Return_Pipe[0];
			string a10 = b10.str();

			execl("./runningstate","running",a1.c_str(),a2.c_str(),a3.c_str(),a4.c_str(),a5.c_str(),a6.c_str(),a7.c_str(),a8.c_str(),buffer.c_str(),a9.c_str(),a10.c_str(),NULL);

			}

			else///parent
			{
					pid4 = fork();

					if(pid4 == 0)
					{

					//call execl for Blocked
					stringstream b1,b2,b3,b4,b5,b6;
					b1<<blocked_ready1;
					string a1 = b1.str();
				
					b2<<running_blocked0_I;
					string a2 = b2.str();

					b3<<main_blocked0;
					string a3 = b3.str();
					
					b4<<BlockedToMain[1];
					string a4 = b4.str();
					//
					b5<<running_blocked0_O;
					string a5 = b5.str();

					b6<<running_blocked0_P;
					string a6 = b6.str();



					execl("./blockedstate","block",a1.c_str(),a2.c_str(),a3.c_str(),a4.c_str(),a5.c_str(),a6.c_str(),NULL);

					}

					else
					{
						pid5 = fork();

						if(pid5 == 0)
						{
							//call execl for exit
							stringstream ss,b1,b2,b3,b4;
							ss<<running_exit0;
							string str1 = ss.str();

							b1<<main_exit0;
							string a1 = b1.str();
							b2<<ExitToMain[1];
							string a2 = b2.str();

							b3<<sizee;
							string a3 = b3.str();

							b4<<DOOM_PIPE[1];
							string a4 = b4.str();

							execl("./exitstate","exit",str1.c_str(),a1.c_str(),a2.c_str(),a3.c_str(),a4.c_str(),buffer.c_str(),NULL);
						}

						else
						{					
							
						}
						
					}			
					
				}				
					
			}
		
		}



//closing the writing end of these pipes
close(NewToMain[1]);
close(BlockedToMain[1]);
close(ReadyToMain[1]);
close(RunningToMain[1]);
close(ExitToMain[1]);

//closing the reading end of these pipes
close(MaintoNew[0]);
close(MaintoReady[0]);
close(MaintoRunning[0]);
close(MaintoBlocked[0]);
close(MaintoExit[0]);




//NOW CLOSING PIPES OF ALL THE SYSTEM IN THE MAIN PROC
close(NewtoReady[0]);
close(NewtoReady[1]);

//FOR READYTORUNNING PIPE
close(ReadytoRunning[0]);
close(ReadytoRunning[1]);


//FOR RUNNINGTOREADY PIPE
close(RunningtoReady[0]);
close(RunningtoReady[1]);

close(RunningtoReady_S[0]);
close(RunningtoReady_S[1]);


//FOR BLOCKEDTOREADY PIPE
close(BlockedtoReady[0]);
close(BlockedtoReady[1]);


//FOR RUNNINGTOBLOCKED PIPE
close(RunningtoBlocked_I[0]);
close(RunningtoBlocked_I[1]);

close(RunningtoBlocked_O[0]);
close(RunningtoBlocked_O[1]);

close(RunningtoBlocked_P[0]);
close(RunningtoBlocked_P[1]);


//FOR RUNNINGTOEXIT PIPE
close(RunningtoExit[0]);
close(RunningtoExit[1]);

close(Return_Pipe[1]);
close(Return_Pipe[0]);



///////////////////////////////



	
int a;


char order[6] ={'R','E','A','D','Y','\0'}; 

char messageN[6];
char messageR[6];
char messageRun[6];
char messageB[6];
char messageE[6];

read(NewToMain[0],messageN,sizeof(messageN));
read(BlockedToMain[0],messageRun,sizeof(messageRun));
read(ReadyToMain[0],messageR,sizeof(messageR));
read(RunningToMain[0],messageRun,sizeof(messageRun));
read(ExitToMain[0],messageRun,sizeof(messageRun));


cout<<"Type an integer to begin the scheduling\n";
cin>>a;

write(MaintoNew[1],order,sizeof(order));
write(MaintoReady[1],order,sizeof(order));
write(MaintoRunning[1],order,sizeof(order));
write(MaintoBlocked[1],order,sizeof(order));
write(MaintoExit[1],order,sizeof(order));






//////DOOM    CLOCK/////

int cont = 1;
int end = 2;
int situation=1;
int clock=0;

while(1)
{
	cout<<"\n\nTHE TIME ON UNIVERSAL CLOCK IS >>"<<clock<<endl;
	clock++;

	read(DOOM_PIPE[0],&situation,sizeof(situation));


	read(NewToMain[0],messageN,sizeof(messageN));
	read(ReadyToMain[0],messageR,sizeof(messageR));
	read(BlockedToMain[0],messageRun,sizeof(messageRun));
	read(RunningToMain[0],messageRun,sizeof(messageRun));
	read(ExitToMain[0],messageRun,sizeof(messageRun));


	if(situation == 2)
	{
		write(MaintoNew[1],&end,sizeof(end));
		write(MaintoReady[1],&end,sizeof(end));
		write(MaintoBlocked[1],&end,sizeof(end));
		write(MaintoExit[1],&end,sizeof(end));
		write(MaintoRunning[1],&end,sizeof(end));
		break;
	}

	else
	{
		write(MaintoNew[1],&cont,sizeof(cont));
		write(MaintoReady[1],&cont,sizeof(cont));
		write(MaintoBlocked[1],&cont,sizeof(cont));
		write(MaintoExit[1],&cont,sizeof(cont));
		write(MaintoRunning[1],&cont,sizeof(cont));

	}

}//end





return 0;
}///end main




