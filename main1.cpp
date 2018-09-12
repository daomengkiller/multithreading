//线程管理，数据竞争和互斥对象
#include <iostream>
#include <thread>
#include <string>
using namespace std;
void function_1(){
    cout<<"www.oxox.work"<<endl;
}
class Fctor{
public:
    void operator()(string& s){

            cout<<this_thread::get_id()<<"from t1 :"<<s<<endl;
            s="Fctor";

    }
};
int main() {
    string s="main";
    cout<<this_thread::get_id()<<endl;
    thread t1((Fctor()),ref(s));//依然为值复制，子线程并没有修改父线程的值，可以使用ref方法
    string s1=move(s);
    cout<<t1.get_id();

    try {
            cout<<"from  main:"<<" "<<s<<endl;


    }
    catch (...){
        t1.join();
        throw;
    }
    t1.join();
    cout<<std::thread::hardware_concurrency()<<endl;
//    function_1();
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}