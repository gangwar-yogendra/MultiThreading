/**
 * Print even and odd using mutithreading
**/

#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <mutex>
#include <fstream>

using namespace std;

std::mutex _mu1;

void _Even()
{
   for(int i=0; i<5; i++) {
       std::unique_lock<mutex> lock1(_mu1, std::defer_lock);
        if(!(i & 1)) {
            //std::lock_guard<mutex> lock1(_mu1);
            lock1.lock();
            cout<< "Even" << ": "<< i << endl;            
            lock1.unlock();
            cout<< "Even\n";
            
            //lock1.lock();
            /* You can lock and unlock again */
            /* using unique_lock<mutex> */            
            //lock1.unlock();
        }
        
    }
}

void _Odd()
{
    for(int i=0; i<5; i++) {
        std::unique_lock<mutex> lock1(_mu1, std::defer_lock);
        if(i & 1) {
            //std::lock_guard<std::mutex> lock1(_mu1);
            lock1.lock();
            cout<< "Odd" << ": "<< i << endl;            
            lock1.unlock();
            cout<< "Odd\n";
        }
    }
}

int main()
{
    std::thread t1(_Even);
    std::thread t2(_Odd);

    usleep(4);
    t1.join();
    t2.join();
    
    return 0;
}
