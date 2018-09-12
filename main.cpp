//时间限制
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

    thread t1(factorial,6);
    this_thread::sleep_for(chrono::milliseconds(3));
    chrono::steady_clock::time_point tp=chrono::steady_clock::now()+chrono::milliseconds(4);
    this_thread::sleep_until(tp);

    mutex mu;
    unique_lock<std::mutex> locker(mu);
    locker.try_lock_for(chrono::milliseconds(3));
    locker.try_lock_until(tp);

    condition_variable cond;
    cond.wait_for(locker,chrono::milliseconds(3));
    cond.wait_until(locker,tp);

    promise<int> p;
    future<int> f=p.get_future();
    f.wait_for(chrono::milliseconds(3));
    f.wait_until(tp);



    return 0;
}