/**
 * Producer and Consumer Problem
 * using mutex and condition variable
**/

#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>

using namespace std;

std::mutex _mutex;
std::deque<int> q;

// Added condition variable
std::condition_variable cond;

void producer()
{
    int count = 10;    
    while(count > 0)
    {
        std::unique_lock<mutex> lock(_mutex);
        q.push_front(count);
        lock.unlock();
        // Condition variable case to notify
        //cond.notify_one();  // Notify once its fill the data in queue and notify 
                            // only one thread
        // If need to notify more than one thread or all thread then 
        cond.notify_all();
        std::this_thread::sleep_for(chrono::seconds(1));    // Sleep thread t1
        count--;
    }
}

void consumer()
{
    int data = 0;    
    while(data != 1)
    {
        std::unique_lock<mutex> lock(_mutex);
    //    if(!q.empty())    // Not required when use condition variable
    //    {                 
            /*             
            sleep the thread t2 till it will not notify and why did pass 
            argument lock in the wait fnction?? So because using unique_lock<>
            acquire the mutex then before sleep the t2 thread we need to release 
            the same acquire mutex, which will call in wait function
            and on notify_one() will acquire the same mutex using lock variable
            */
            //cond.wait(lock);  // it will sleep and will not wakeup till notify 
            cond.wait(lock, [](){return !q.empty();});  //suprious wake
            data = q.back();
            q.pop_back();
            lock.unlock();            
            cout<<"Thread t2 get value from thread t1:"<<data<<endl;
    //    }
        /* This below code is busy waiting unnecessarily 
           lock the mutex and then check if there are no
           data in queue then unlock the mutex and 
           again will reach to while loop
        */
        /* To avoid this case we use condition variable */
    //    else
    //    {
    //        lock.unlock();
    //    }
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    
    return 0;
}
