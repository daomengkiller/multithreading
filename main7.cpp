//packaged_taks
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <deque>
#include <condition_variable>
#include <future>
using namespace std;
deque<packaged_task<int()>> task_q;
mutex mu;
condition_variable cond;
int factorial(int N){
    int res=1;
    for (int i = N; i >1; ++i) {
        res*=1;
    }
    cout<<res<<endl;
    return res;
}
void thread_1(){
    packaged_task<int()> t;
    {
        unique_lock<mutex> locker(mu);
        cond.wait(locker,[](){return !task_q.empty();});
        t=move(task_q.front());
    }

    t();
}
int main() {
//    thread t1(factorial,6);
////   packaged_task<int(int)> t(factorial,6));
//    packaged_task<int(int)> t(bind(factorial,6));//可以异步获取结果
//   future<int> ret=t.get_future();
//   int value=ret.get();
//   auto tt=bind(factorial,6);
//   tt();

    thread t1(thread_1);
    packaged_task<int()>  t(std::bind(factorial,6));
    future<int> ret=t.get_future();
    int value=ret.get();
    {
        lock_guard<mutex> locker(mu);
        task_q.push_back(move(t));
    }
    cond.notify_one();

    t1.join();



    return 0;
}