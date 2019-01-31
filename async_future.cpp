/**
#1:- Used std::future to pass value (or return value) from child thread to parent thread
**/

#include <iostream>
#include <thread>
#include <future>

using namespace std;

int factorial( int N )
{
	int res = 1;
	for(int i=N; i>1; i--)
	{
		res *= i;
	}
	
	return res;
}

int main()
{
	int x;
	
    /* async function may or may not be create another thread */
    // std::future<int> fu = std::async(factorial, 4);
    // std::future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial, 4);
	
    /* async function will not create another thread if we pass std::launch::deferred */
    // std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
	
    /* async function will create another thread if we pass std::launch::async */
	std::future<int> fu = std::async(std::launch::async, factorial, 4);
	
	x = fu.get();	// call only once if will call again 
					// the fu.get() program will crash
					
	cout<<"Factorial value of 4: "<<x<<endl;
	
}
