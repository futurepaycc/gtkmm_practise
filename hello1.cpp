#include <gtkmm.h>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "titile");
    Gtk::Window window;
    window.set_title("这是一个测试");
    window.set_default_size(800, 600);

    return app->run(window);
}