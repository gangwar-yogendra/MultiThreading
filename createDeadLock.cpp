/** 
 * Create a dead lock using shared_print and 
 * shared_print_1 using 2 mutex, if the will 
 * arrange call as crisscross format 
 * To stop dead loak you must call the both mutex
 * guard lock should if in the same sequencial form
 * as they called in function 1 or vice-versa
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
        std::lock_guard<std::mutex> lock1(_mu1);
        std::lock_guard<std::mutex> lock2(_mu2);
        cout<< "From" << ": "<<msg << value << endl;
    }
    
    void shared_print_1(string msg, int value){    
        std::lock_guard<std::mutex> lock2(_mu2);   /* This code will create the dead lock */
        std::lock_guard<std::mutex> lock1(_mu1);   /* To avoid the dead lock call this lock1 above lock2 */
	                                           /* as given in function shared_print() */
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

