#include "mygtkmm.h"

using namespace std;

class AlienDetector {
   public:
    AlienDetector() {}

    void run() {
        cout << "AlientDetctor is running" << endl;
        signal_detected();  //发出事件
    }

    sigc::signal<void> signal_detected;
};

void warn_people() {  //事件回调函数 -> 槽函数
    cout << "Therer are alines in the carpark" << endl;
}

int main(int argc, char const *argv[]) {
    AlienDetector myDetector;
    myDetector.signal_detected.connect(sigc::ptr_fun(warn_people)); //链接普通函数
    myDetector.run();
    return 0;
}
