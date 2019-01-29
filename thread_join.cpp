/* Join thread */

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
	
    myThread.join();	// main thread will to finish myThread
	
    return 0;
}
