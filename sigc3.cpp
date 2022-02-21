#include "mygtkmm.h"

using namespace std;

void clicked() { cout << "click" << endl; }

void handleKeyEvent(GdkEventKey *event,Gtk::Window* window){
    window->resize(800,600);
    if (event->keyval == GDK_KEY_a) {
        cout << "你按下了a" << endl;
    }
    cout << "press" << endl;
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "title");
    Gtk::Window window; //栈上定义window,不用delete
    window.set_default_size(400, 300);

    Gtk::Button button1("button1");
    button1.signal_clicked().connect(sigc::ptr_fun(clicked));

    //NOTE: 1. 使用这种方式才能处理上下文变量window, 业务复杂再传参调用外部函数
    window.signal_key_press_event().connect([&](GdkEventKey *event) {
        handleKeyEvent(event,&window);
        return true; //NOTE: 2. 这里用来匹配槽函数返回类型，不可省略
    });

    window.add(button1);
    window.show_all();
    app->run(window);
    return 0;
}
