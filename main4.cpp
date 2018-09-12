//条件变量
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <deque>
#include <condition_variable>
using namespace std;
deque<int> q;
mutex mu;
condition_variable cond;
void function_1(){
    int count=10;
    while(count>0){
        unique_lock<mutex> locker(mu);
        q.push_back(count);
        locker.unlock();
        cond.notify_one();//激活一个触发线程
        this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}
void funtion_20(){
    int data=0;
    while(data!=1){
        unique_lock<mutex> locker(mu);
        if(!q.empty()){
            data=q.back();
            q.pop_back();
            locker.unlock();
            cout<<"t2: "<<data<<endl;
        } else{
            locker.unlock();
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
}
void funtion_2(){
    int data=0;
    while(data!=1){
        unique_lock<mutex> locker(mu);
        cond.wait(locker,[](){ return !q.empty();});//cond会将locker解锁，必须为unique_lock,然后休眠，直到被唤醒。

            data=q.back();
            q.pop_back();
            locker.unlock();
            cout<<"t2: "<<data<<endl;
    }
}
int main() {
    thread t1(function_1);
    thread t2(funtion_2);
    t1.join();
    t2.join();



    return 0;
}