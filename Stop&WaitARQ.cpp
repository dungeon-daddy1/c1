#include<iostream>
#include <time.h>
#include <cstdlib>
#include<ctime>
#include <unistd.h>
using namespace std;
class timer 
{
private:
   	unsigned long begTime;
public:
	void start() 
	{
  		begTime = clock();
	}
	unsigned long elapsedTime() 
	{
  		return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
	}
	bool isTimeout(unsigned long seconds) 
	{
  		return seconds >= elapsedTime();
 	}
};
int N=5;
int main()
{
	int frames[N];
	for(int i=0;i<N;i++)
	{
		frames[i] = i+1; 
	}
 	
	unsigned long seconds = 5;
	
 	srand(time(NULL));
 	timer t;
 	cout<<"Sender has to send frames : ";
 	for(int i=0;i<N;i++)
	 cout<<frames[i]<<" ";
 	cout<<endl;
 	int count = 0;
 	bool delay = false;
 	cout<<endl<<"Sender\t\t\t\t\tReceiver"<<endl;
 	do
 	{
    	bool timeout = false;
     	cout<<"Sending Frame : "<<frames[count];
     	cout.flush();
     	cout<<"\t\t";
     	t.start();
     	if(rand()%2)
     	{
        	int to = 24600 + rand()%(64000 - 24600)  + 1;
         	for(int i=0;i<64000;i++)
			 for(int j=0;j<to;j++) {}
     	}
     	if(t.elapsedTime() <= seconds)
     	{
        	cout<<"Received Frame : "<<frames[count]<<" ";
         	if(delay)
         	{
            	cout<<"Duplicate";
             	delay = false;
         	}
         	cout<<endl;
         	count++;
     	}
     	else
     	{
        	cout<<"---"<<endl;
         	cout<<"Timeout"<<endl;
         	timeout = true;
     	}
     	t.start();
     	if(rand()%2 || !timeout)
     	{
    		int to = 24600 + rand()%(64000 - 24600)  + 1;
         	for(int i=0;i<64000;i++)
            	for(int j=0;j<to;j++) {}
         	if(t.elapsedTime() > seconds )
         	{
            	cout<<"Delayed Ack"<<endl;
             	count--;
             	delay = true;
         	}
         	else if(!timeout)
            	cout<<"Acknowledgement : "<<frames[count]-1<<endl;
     	}
 	}while(count!=N);
 	return 0;
}
