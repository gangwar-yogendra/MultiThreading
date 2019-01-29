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
        //cond.notify_one();  // notify only one thread
        cond.notify_all();    // notify more all thread
        std::this_thread::sleep_for(chrono::seconds(1));    // Sleep thread t1 for 1 second
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
            Sleep the thread t2 using given below function wait(), till it will not 
            notify using other thread t1 using function notify_all/notify_one 
            and there we need to pass argument argument in wait function as unique_lock<> obj
            , because using unique_lock<> object will acquire the mutex and we need to release 
            before sleeping the t2 thread, so the wait function will call unlock function to 
            release the acquire mutex
            */
            //cond.wait(lock);  // it will sleep and will not wakeup till notify 
            cond.wait(lock, [](){return !q.empty();});  //suprious wake
            data = q.back();
            q.pop_back();
            lock.unlock();            
            cout<<"Thread t2 get value from thread t1:"<<data<<endl;
    //    }
        /* The below code is busy waiting unnecessarily 
           there lock the mutex and then check if there are no
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
