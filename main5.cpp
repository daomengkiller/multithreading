//futurn,pomise
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <deque>
#include <condition_variable>
#include <future>
using namespace std;
int factorial(shared_future<int>& f){
    int N=f.get();//若没有,会抛出异常
    int res=1;
    for (int i = N; i >1 ; --i) {
        res*=i;
    }
    cout<<res<<endl;
    return res;
}
int main() {
//    thread t1(factorial,4);
//    t1.join();
    promise<int> p;
    future<int> f=p.get_future();
    shared_future<int> sf=f.share();
      future<int> fu=async(std::launch::async, factorial,ref(sf));//std::launch::async为创建子线程，deferred在此线程运行
    future<int> fu1=async(std::launch::async, factorial,ref(sf));
    future<int> fu2=async(std::launch::async, factorial,ref(sf));
p.set_value(4);
        int x=fu.get();
        cout<<x<<endl;



    return 0;
}