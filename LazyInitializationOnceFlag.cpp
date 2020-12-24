#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

class LogFile
{
    std::mutex mu1;
    //std::mutex mu_open;
    /* Called Lazy Initialization */
    std::once_flag _flag;
    ofstream f;
    
public:
    /* We do not need file open when we call the program */
    /* Only open log file when need to write the log into file */
    /* So comment below code
    /* 
    LogFile()
    {
        f.open("log.txt");
    }
    */
    
    void shared_print(string s, int id)
    {
        /* When shared_print will call then only open the file */
        /* 1. Problem in multithread code that each thread will try to open the log file */
        //if(!f.is_open())
        //{
        //    f.open("log.txt");
        //}
        
        /* For above problem we need to include the mutex before opening the file */
        /* 2.  But this also will get issue with multi thread programming */
        //if(!f.is_open())
        //{
            /* t1 and t2 thread will get file is not open and acquire the lock on thread t1 and t2
               before open the log.txt file */
            /* And both the thread will lock at same time  */
            //std::unique_lock<std::mutex> lock(mu_open);
            //f.open("log.txt");
        //}
        
        /* For above problem we need to include the mutex before opening the file */
        /* 3.  But this also will get issue with multi thread programming */
        /* its thread safe but multiple times if we need to call shared_print() function 
            then again locking and unlocking is wastage of computer resources */
        //std::unique_lock<std::mutex> lock(mu_open);
        //if(!f.is_open())
        //{
        //    f.open("log.txt");
        //}

        /* Called Lazy Initialization */
        std::call_once(_flag, [&]() {f.open("log.txt"); });
        
        std::unique_lock<std::mutex> lock(mu1);
        f << "From " << s << ": " << id << "\n";
        lock.unlock();
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
        log.shared_print("main", i);
    }
    t1.join();
    
    return 0;
}
