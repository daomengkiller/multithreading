//创建线程的方式
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <deque>
#include <condition_variable>
#include <future>
using namespace std;
class A{
public:
    void f(int x,char c){

    }
    int operator()(int N){
        return 0;
    }
};
void foo(int x){
    return;
}
int main() {
    A a;
    thread t1(a,6);
    thread t2(ref(a),6);
    thread t3(move(a),6);
    thread t4(A(),6);

    thread t5(foo,6);
    thread t6([](int x){ return;},6);

    thread t7(&A::f,a,8,'w');//传递a的拷贝的成员函数给子线程
    thread t8(&A::f,&a,8,'w');
    async(launch::async,a,6);



    return 0;
}