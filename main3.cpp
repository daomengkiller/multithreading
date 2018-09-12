//unique lock和Lazy initialization
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
//        {
//            unique_lock<mutex> locker(m_mutex_open,defer_lock);//这样保证了文件只被打开一次
//            if(!f.is_open()){
//                f.open("log.txt");
//            }
//        }消耗资源多，使用一下方法
        call_once(m_flag,[&](){ f.open("log.txt");});


//    mu.lock();
        unique_lock<mutex> locker(m_mutex,defer_lock);//为指定的代码加锁，可以使用move移动锁的控制权，defer_lcok为暂时不加锁
        //...
        locker.lock();


        cout<<msg<<id<<endl;
        //...
        locker.unlock();

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
    mutex m_mutex_open;
    once_flag m_flag;
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
           log.share_print("From main:",i);
        }
    }catch(...) {
        t1.join();

    }
    t1.join();

    return 0;
}