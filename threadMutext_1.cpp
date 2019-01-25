// Example program
#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <mutex>
#include <fstream>

using namespace std;

class LogFile
{
    std::mutex m_mutex;
    ofstream f;
public:
    LogFile() {
        f.open("log.txt");
    }
    
    void shared_print(string msg, int value){    
        std::lock_guard<std::mutex> guard(m_mutex); //RAII
        f<< "From" << ": "<<msg << value << endl;
    }
    
    /* Never return the f to the outside world */
    //ofstream& getStream() { return f; }
    /* Never use as f as argument */
    //void processf(void function(ofstream&)){
    //    fun(f);
    //}
};

void Function_1(LogFile &log)
{
    for(int i=0; i>=-100; i--) {
        log.shared_print(string("Child Thread: "), i);
    }
}

int main()
{
    LogFile log;
    std::thread t1(Function_1, std::ref(log));
  
    for(int i=0; i<=100; i++) {
        log.shared_print(string("Main Thread: "), i);
    }
    t1.join();
  
    return 0;
}

