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

class EvenOdd
{
    std::mutex _mu1;
public:
    EvenOdd() {
    }

    void printEven(){
        for(int i=0; i<30; i++) {
            if(!(i & 1)) {
                std::lock_guard<std::mutex> lock1(_mu1);
                cout<< "Even" << ": "<< i << endl;
            }
        }
    }

    void printOdd(){
        for(int i=0; i<30; i++) {
            if(i & 1) {
                std::lock_guard<std::mutex> lock1(_mu1);
                cout<< "Odd" << ": "<< i << endl;
            }
        }
    }
};


void _Even(EvenOdd &l)
{
    l.printEven();
}

void _Odd(EvenOdd &l)
{
    l.printOdd();
}

int main()
{
    EvenOdd oe;
    std::thread t1(_Even, std::ref(oe));
    std::thread t2(_Odd, std::ref(oe));

    usleep(4);
    t1.join();
    t2.join();


    return 0;
}


