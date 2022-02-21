#include "mygtkmm.h"
#include <cairomm/cairomm.h>
#include <gdk/gdkevents.h>
#include <goocanvasmm.h>

/* 
说明: 原来程序有编译bug
来源:https://github.com/GNOME/goocanvasmm/tree/master/examples/simple
make sourcename=goocanvas1
*/

class ExampleWindow : public Gtk::Window {
   public:
    ExampleWindow();
   protected:
    Goocanvas::Canvas m_canvas;
    Glib::RefPtr<Goocanvas::Rect> m_table;
    bool on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& target, _GdkEventButton* event); //这里类型提换了
};

ExampleWindow::ExampleWindow() {
    set_title("goocanvasmm - Simple Example");
    m_canvas.set_size_request(640, 480);
    m_canvas.set_bounds(0, 0, 1000, 1000);
    auto root = m_canvas.get_root_item();

    auto rect = Goocanvas::Rect::create(100, 100, 400, 400);
    root->add_child(rect);
    rect->property_line_width() = 10.0;
    rect->property_radius_x() = 20.0;
    rect->property_radius_y() = 20.0;
    rect->property_stroke_color() = "yellow";
    rect->property_fill_color() = "red";
    rect->signal_button_press_event().connect(sigc::mem_fun(*this, &ExampleWindow::on_rect_button_press), true);

    auto text = Goocanvas::Text::create("Hello World", 300, 300, -1, Goocanvas::AnchorType::ANCHOR_CENTER);
    root->add_child(text);

    text->property_font() = "Sans 24";

    text->rotate(45, 300, 300);

    auto sw = Gtk::manage(new Gtk::ScrolledWindow());
    sw->add(m_canvas);
    add(*sw);
}

bool ExampleWindow::on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& target, _GdkEventButton* event) {
    std::cout << "You clicked the rectangle." << std::endl;
    return true;
}

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "title");
    ExampleWindow window;  //栈上定义window,不用delete
    window.set_default_size(600, 600);

    Gtk::Button button1("button1");
    button1.signal_clicked().connect([&]{
        using namespace std;
        cout << "别瞎按" << endl;
    });

    window.add(button1);
    window.show_all();
    app->run(window);
    return 0;
}
