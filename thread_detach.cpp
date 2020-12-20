#include <iostream>
#include <thread>
#include <unistd.h>

void _Function()
{
    std::cout<<"_Function\n";
}

/* Main function is the main thread for this program */
int main(int argc, char** argv)
{
    /* Creating another thread in main thread */
    std::thread myThread(_Function);
	
    /* We can use detach() also */
     usleep(14);
     myThread.detach();		/* Main thread will freely on its own, */
				/* It will works like daemon process */
	
    /* We can join the same thread if thread is joinable */
    if(myThread.joinable())	/* If condition will not insert then program will crash */
        myThread.join();	/* Because detachable thread cannot be join and vice versa */
	
	
    return 0;
}
