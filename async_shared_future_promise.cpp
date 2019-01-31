/**
 * If factorial function need to launch many times in the below scenario
 * Pass the value from parent thread to child thread using std::promise 
 * not at the time of creating the thread but after sometime or in future
 * and send value from child thread to parent thread using std::future
 * we will use std::future and std::promise
**/

#include <iostream>
#include <thread>
#include <future>

using namespace std;


int factorial( std::shared_future<int> f )
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
	std::promise<int> p;
	std::future<int> f = p.get_future();
	
    /* 
        Problem: In below commented code problem is, the code "int N = f.get();" in 
        child thread will call mutiple if we pass argement as std::future<int> &f
        times which will get issue because we can not call multiple 
        times the f.get() for different calling in main thread
    */
	//std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
	//std::future<int> fu2 = std::async(std::launch::async, factorial, std::ref(f));
	//std::future<int> fu3 = std::async(std::launch::async, factorial, std::ref(f));
	//... 10 thread
	
	/* 
	    Solution: The below code is the solution for above problem
	*/
	std::shared_future<int> sf = f.share();
	
	std::future<int> fu = std::async(std::launch::async, factorial, sf);
	std::future<int> fu2 = std::async(std::launch::async, factorial, sf);
	std::future<int> fu3 = std::async(std::launch::async, factorial, sf);
	//... 10 thread
	
	
	// do something else
	// Or Wait for some times and then will send the value 
	// from parent thread to child thread
	std::this_thread::sleep_for(chrono::milliseconds(200)); 
	/* Test this line make uncomment the below 1 line and comment the below line 2-3 of this code */
	//p.set_exception(std::make_exception_ptr(std::runtime_error("Did not send the value for child thread")));
	p.set_value(5);
					
	cout<<"Factorial value of 5 get in parent thread: "<<fu.get()<<endl;	
	cout<<"Factorial value of 5 get in parent thread: "<<fu2.get()<<endl;
	cout<<"Factorial value of 5 get in parent thread: "<<fu3.get()<<endl;
	
}
