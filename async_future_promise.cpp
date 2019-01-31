/**
 * Pass the value from parent thread to child thread using std::promise 
 * not at the time of creating the thread but after sometime or in future
 * and send value from child thread to parent thread using std::future
 * we will use std::future and std::promise
**/

#include <iostream>
#include <thread>
#include <future>

using namespace std;


int factorial( std::future<int> &f )
{
    int res = 1;
    
    /*  Child thread will get the value 5 in 
        variable N, it was set in parent thread main()
        using set_value function of promise variable
    */    
    int N = f.get(); //exception: std::future_errc::broken_promise
    
    cout<<"Value of N get in child thread: " <<N<<"\n";
    
    for(int i=N; i>1; i--)
    {
        res *= i;
    }
	
    return res;
}

int main()
{
	int x;
	
	std::promise<int> p;
	std::future<int> f = p.get_future();
	
	/* future can not copy form one object to other, it can be only move */
	// std::future<int> f2 = f; // Error
	//std::future<int> f2 = std::move(f); // No Error
	
	
    /* async function will create another thread if we pass std::launch::async */
	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
	
	// do something else
	// Or Wait for some times and then will send the value 
	// from parent thread to child thread
	std::this_thread::sleep_for(chrono::milliseconds(2000)); 
	/* Test this line make uncomment the below 1 line and comment the below line 2-3 of this code */
	//p.set_exception(std::make_exception_ptr(std::runtime_error("Did not send the value for child thread")));
	p.set_value(5);
	x = fu.get();	// call only once if will call again 
					// the fu.get() program will crash
					
	cout<<"Factorial value of 5 get in parent thread: "<<x<<endl;
	
}
