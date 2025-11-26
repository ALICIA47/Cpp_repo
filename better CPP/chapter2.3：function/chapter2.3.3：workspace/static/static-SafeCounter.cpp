#include<iostream>
#include<mutex>
#include<thread>

class SafeCounter{
public:
    static int count;
    static std::mutex mutex;//互斥锁
    static void increment(){
        std::lock_guard<std::mutex>lock(mutex);//锁定互斥锁，防止多线程同时访问
        ++count;
        //lock_guard对象被销毁时解锁
    }
};
int SafeCounter::count=0;
std::mutex SafeCounter::mutex;
int main(){
    std::thread threads[10];
    for(int i=0;i<10;i++){
        threads[i]=std::thread(SafeCounter::increment);
    }
    for(auto& t:threads){
        t.join();
    }
    std::cout<<"Final count: "<<SafeCounter::count<<std::endl;
    return 0;
}