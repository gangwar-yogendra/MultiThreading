/**
 * Dead lock avoidance using std::lock() and
 * std::adopt_lock in std::lock_guard
**/

#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <mutex>
#include <fstream>

using namespace std;

class LogFile
{
    std::mutex _mu1;
    std::mutex _mu2;
    ofstream f;
public:
    LogFile() {
        f.open("log.txt");
    }
    
    void shared_print(string msg, int value){
        std::lock(_mu1, _mu2);
        std::lock_guard<std::mutex> lock1(_mu1, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(_mu2, std::adopt_lock);
        
        cout<< "From" << ": "<<msg << value << endl;
    }
    
    void shared_print_1(string msg, int value){    
        std::lock(_mu1, _mu2);
        std::lock_guard<std::mutex> lock1(_mu1, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(_mu2, std::adopt_lock);
        
        cout<< "From" << ": "<<msg << value << endl;
    }
};

void Function_1(LogFile &log)
{
    for(int i=0; i>=-100; i--) {
        /* Child thread will call 'shared_print' function */
        log.shared_print(string("Child: "), i);
    }
}

int main()
{
    LogFile log;
    std::thread t1(Function_1, std::ref(log));
  
    for(int i=0; i<=100; i++) {
        /* Main thread will call 'shared_print_1' function */
        log.shared_print_1(string("Main Thread: "), i);
    }
    t1.join();
  
    return 0;
}

