# CPU-Scheduling-Simulator

1)Run the commands below on the terminal to start the scheduler.

g++ -pthread -o readystate ready.cpp

g++ -pthread -o blockedstate blocked.cpp

g++ -o newstate new.cpp

g++ -o exitstate exit.cpp

g++ -o runningstate running.cpp

g++ main.cpp

./a.out

2)The Process Name, Waiting Time ,  Trunaround Time and Burst time are recorded in a file named "processes_stats.txt"

3)The  Average Waiting Time , Average Trunaround Time and Burst time are recorded in a file named "processes_Avg.txt" which are uploaded every 30 seconds

4)All procs are read from processes.txt (You can change the procs as you like)

5)In the end on the terminal a text will appear by the name of "End clock activated" and all the processes will be displayed on the terminal,then press (Ctrl+c) to end it.

6)If there are any difficulties or any wierd errors popping up please consult me and I would be happy to explain any part of the code over a live session.



Errors:
RUN THESE COMMANDS EVERYTIME THE SCHEDULER IS CHANGED AND IF THE PROGRAM BECOMES STUCK PRESS (Ctrl+c) compile and run again.

Output:

![image](https://user-images.githubusercontent.com/64328883/158459811-bccbf1b1-0e87-4b01-af33-292e5902ddb1.png)



