//死锁
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
using namespace std;
mutex mu;
class lofFile{
public:
    lofFile(){
        f.open("log.txt");
    }
    void share_print(string msg,int id){
//    mu.lock();
        lock(m_mutex,m_mutex2);
        lock_guard<mutex> guard(m_mutex,adopt_lock);//保证异常时，能自动解锁。
        lock_guard<mutex> guard2(m_mutex2,adopt_lock);
        cout<<msg<<id<<endl;
//    mu.unlock();
    }
    void share_print1(string msg,int id){
//    mu.lock();
        lock(m_mutex2,m_mutex);
        lock_guard<mutex> guard2(m_mutex2,adopt_lock);

        lock_guard<mutex> guard(m_mutex,adopt_lock);//保证异常时，能自动解锁。

        cout<<msg<<id<<endl;
//    mu.unlock();
    }
    ofstream&  GetStream(){
        return f;
    }//会将f暴露，被别的程序修改
    void processf(void fun(ofstream&))
    {
        fun(f);
    }//会将f暴露，被别的程序修改
protected:
private:
    mutex m_mutex;
    mutex m_mutex2;
    ofstream f;

};
void share_print(string msg,int id){
//    mu.lock();
    lock_guard<mutex> guard(mu);//保证异常时，能自动解锁。
    if(id==5)
        throw;
    cout<<msg<<id<<endl;
//    mu.unlock();
}
void funtion_1(lofFile& log){

    for (int i = 0; i > -10; --i) {
        log.share_print("From t1:",i);
    }
}
int main() {
    lofFile log;
    thread t1(funtion_1,ref(log));
    try{
        for (int i = 0; i < 10; ++i) {
           log.share_print1("From main:",i);
        }
    }catch(...) {
        t1.join();

    }
    t1.join();

    return 0;
}