/* 
预编译头文件加速尝试，没啥用!
g++ -c -include mygtkmm.h -g `pkg-config --cflags-only-I --libs gtkmm-3.0`  `pkg-config --cflags --libs goocanvasmm-2.0` hello2.cpp -o bin/hello2.o
clang++ -c -include mygtkmm.h -g `pkg-config --cflags-only-I --libs gtkmm-3.0` hello2.cpp -o bin/hello2.o
clang++ -g -include mygtkmm.h `pkg-config --cflags-only-I --libs gtkmm-3.0` hello2.cpp -o bin/hello2
https://www.zybuluo.com/lniwn/note/829707
*/

#include "mygtkmm.h"

using namespace std;

void clicked(){
    cout<<"click"<<endl;
}

bool onKeyPress(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_a) {
        std::cout << "你按下了a" << std::endl;
    }
    std::cout << "press" << std::endl;
    return true;
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc,argv,"title");
    Gtk::Window window;
    // window.set_title("再测试下");
    window.set_default_size(400,300);

    Gtk::Button button1("button1");
    button1.signal_clicked().connect([&]{ //&代表引用捕获: https://en.cppreference.com/w/cpp/language/lambda
        window.resize(800,600);
        clicked();
    });

    window.signal_key_press_event().connect(sigc::ptr_fun(&onKeyPress)); //sigc::ptr_fun包装非成员函数，接收方可以获取事件类型

    window.add(button1);
    window.show_all();
    app->run(window);
    return 0;
}
