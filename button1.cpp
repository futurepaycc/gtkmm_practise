#include <gtkmm.h>

#include <iostream>

void clicked() { std::cout << "hello" << std::endl; }

int main(int argc,char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Gtk::Window window;
    window.set_default_size(800, 800);

    Gtk::Button button("test1");
    button.signal_clicked().connect(sigc::ptr_fun(&clicked));

    window.add(button);
    button.show();
    return app->run(window);
}