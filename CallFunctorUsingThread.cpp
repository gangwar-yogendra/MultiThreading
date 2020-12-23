/** 
    Passing functor on creation of thread object
    For test as reference enable line:11, 30
    And disable lines: 15, 27 
**/

#include <iostream>
#include <thread>
#include <unistd.h>

class FunctorClass
{
public:
    // void operator () (std::string &str) /* Passing argument as reference */
                                           /* will get compilation error because */
                                           /* passing value in calling function */
    void operator () (std::string str)  /* Passing argument as value */
    {
        std::cout<<"myThread: "<< str <<" "<<std::endl;
        str = "Check reference for string ";
    }
};

/* Main function is the main thread for this program */
int main(int argc, char** argv)
{
    std::string s = "My test string ";
    /* Creating another thread in main thread */
    std::thread myThread((FunctorClass()), s);
    
    /* Check reference code after enable the below code */
    /* And disable the pass by value code */
    // std::thread myThread((FunctorClass()), std::ref(s));
	
    myThread.join();
    
    std::cout<<"Main Thread: "<<s<<" "<<std::endl;	
	
    return 0;
}
