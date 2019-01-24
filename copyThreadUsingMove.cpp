/** 
    Copy one thread into othere thread using std::move 
**/

#include <iostream>
#include <thread>
#include <unistd.h>

class FunctorClass
{
public:
    void operator () (std::string &str)
    {
        std::cout<<"Child thread id: "<<std::this_thread::get_id()<<"\n";
        std::cout<<"myThread: "<< str <<" "<<std::endl;
        str = "Check reference for string ";
    }
};

/* Main function is the main thread for this program */
int main(int argc, char** argv)
{
    std::string s = "My test string ";
    
    std::cout<<"Main thread id: "<<std::this_thread::get_id()<<"\n";
    
    /* Creating another thread in main thread */
    std::thread myThread((FunctorClass()), std::ref(s));    
    std::cout<<"myThread id: "<<myThread.get_id()<<"\n";  	
    //myThread.join();
    
    
    std::thread myThread2(std::move(myThread));
    std::cout<<"myThread2 id: "<<myThread2.get_id()<<"\n";
    myThread2.join();
    
    std::cout<<"Main Thread: "<<s<<" "<<std::endl;	
	
    return 0;
}