// std::unique_lock<std::mutex> use for extra flexibility
// But std::unique_lock<std::mutex> cost is high as compare to
// std::lock_guard<std::mutex>

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

class LogFile
{
    std::mutex mu1;
    std::mutex mu2;
    ofstream f;
    
public:
    void shared_print(string s, int id)
    {
        std::unique_lock<std::mutex> lock(mu1);
        cout << "From " << s << ": " << id << "\n";
        lock.unlock();
    }
    
    void shared_print2(string s, int id)
    {
        std::unique_lock<std::mutex> lock(mu1, std::defer_lock);
        // Do some functionality 
        //
        //
        lock.lock();
        cout << "From " << s << ": " << id << "\n";
        lock.unlock();
        // Do some functionality 
        //
        //
        lock.lock();
        cout << "Again lock" << "\n";
        lock.unlock();   
        
        // Can not be copy only move
        std::unique_lock<std::mutex> lock1 = std::move(lock); 
    }
};

void function1(LogFile &log)
{
    for(int i=0; i>-100; i--)
    {
        log.shared_print("t1", i);
    }
}

int main()
{
    LogFile log;
    std::thread t1(&function1, std::ref(log));
    
    for(int i=0; i<100; i++)
    {
        log.shared_print2("main", i);
    }
    t1.join();
    
    return 0;
}
