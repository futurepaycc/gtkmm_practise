#include <mygtkmm.h>

using namespace std;

class AlienDetector {
   public:
    AlienDetector() {}

    void run() {
        cout << "AlientDetctor is running" << endl;
        signal_detected("carpark");  //发出事件
    }
    //void: 返回类型，string:槽函数参数
    sigc::signal<void,string> signal_detected;
};

void warn_people(string where) {  //事件回调函数 -> 槽函数
    cout << "Therer are alines in the "<<where << endl;
}

/* 
ptr_fun: 普通槽函数
mem_fun: 成员槽函数
 */
int main(int argc, char const *argv[]) {
    AlienDetector myDetector;
    myDetector.signal_detected.connect(sigc::ptr_fun(warn_people)); //链接普通函数
    myDetector.run();
    return 0;
}
