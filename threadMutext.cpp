// Example program
#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <mutex>

using namespace std;

std::mutex mtx;

void shared_print(string msg, int id){

    std::lock_guard<std::mutex> guard(mtx); //RAII
    //mtx.lock();           /* Sould not use directoly because if next line will */
                            /* throw the exception then it will create a dead lock */
    cout<<msg<<id<<endl;    /* Still there are cout is global object so it will lock */
                            /* And make problem for code so check threadMutext_1.cpp */
    //mtx.unlock();
}

void Function_1()
{
    for(int i=0; i>=-100; i--) {
        shared_print("Child Thread: ", i);
    }
}

int main()
{
  std::thread t1(Function_1);
//  usleep(3);
  for(int i=0; i<=100; i++) {
        shared_print("Main Thread: ", i);
  }
  t1.join();

  return 0;
}

