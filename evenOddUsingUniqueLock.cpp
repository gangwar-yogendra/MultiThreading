#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <condition_variable>


using namespace std;

std::mutex _mu1;
int count = 0;
std::condition_variable cond;

bool CheckOdd(int value)
{
    if(value & 1) 
        return true;
        
    return false;
}

bool CheckEven(int value)
{
    if(!(value & 1)) 
        return true;
        
    return false;
}

void _Even()
{
    while(count < 200) {
        std::unique_lock<std::mutex> lock(_mu1);
        cond.wait(lock, [](){ return CheckEven(count);});
        if(!(count & 1)) {
            cout<< "Even" << ": "<< count << endl;
            count++;
            lock.unlock();
        }
        cond.notify_all();
        std::this_thread::sleep_for(chrono::milliseconds(100));
        //std::this_thread::sleep_for(chrono::seconds(1));
    }
}

void _Odd()
{
    while(count < 200) {
        std::unique_lock<std::mutex> lock(_mu1);
	cond.wait(lock, [](){ return CheckOdd(count);});
        if(count & 1) {
            cout<< "Odd" << ": "<< count << endl;
            count++;
            lock.unlock();
        }
        cond.notify_all();
        std::this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main()
{
    std::thread t1(_Even);
    std::thread t2(_Odd);
	
    t1.join();
    t2.join();
	
    return 0;
}
