#include <mygtkmm.h>

using namespace std;

void clicked() { std::cout << "hello" << std::endl; }

/* 
使用lamda代替sigc
https://stackoverflow.com/questions/13805883/use-lambda-in-connection-with-sigc-library
 */
int main(int argc,char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Gtk::Window window;
    window.set_default_size(800, 800);

    Gtk::Button button("test1");
    // button.signal_clicked().connect(sigc::ptr_fun(&clicked));
    button.signal_clicked().connect([&window,&button]{
        cout<<"clicked ..."<<endl;
        window.resize(200,300);
        button.set_label("test again");
    });

    window.add(button);
    button.show();
    return app->run(window);
}