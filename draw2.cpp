#include "mygtkmm.h"
/*
signal_draw函数绑定说明：
https://stackoverflow.com/questions/7771623/segfault-when-creating-smartpointer-on-cairocontext
https://developer.gnome.org/gtkmm-tutorial/stable/sec-binding-extra-arguments.html.en (bind额外参数)
https://www.cairographics.org/documentation/cairomm/reference/classCairo_1_1RefPtr.html(是个智能指针)
https://www.cnblogs.com/tenosdoit/p/3456704.html (智能指针讲解)
*/

bool draw(const Cairo::RefPtr<Cairo::Context> &context, Gtk::DrawingArea *drawarea) {
    Gtk::Allocation allocation = drawarea->get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    context->set_source_rgb(1.0, 0.0, 0.0);
    context->set_line_width(2.0);
    context->move_to(0, 0);
    context->line_to(width, height);
    context->stroke();

    return true;
}

bool onKeyPress(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_a) {
        std::cout << "你按下了a" << std::endl;
    }
    std::cout << "press" << std::endl;
    return true;
}

int main(int argc, char *argv[]) {
    Gtk::Main app(argc, argv);
    Gtk::Window window;
    Gtk::DrawingArea drawarea;
    window.set_default_size(800, 600);

    drawarea.signal_draw().connect(sigc::bind(sigc::ptr_fun(&draw), &drawarea));
    window.add(drawarea);
    window.show_all();

    window.signal_key_press_event().connect(sigc::ptr_fun(&onKeyPress));

    Gtk::Main::run(window);
    return 0;
}