// #include <gtkmm.h>
// #include <iostream>
#include <mygtkmm.h>

#include <goocanvasmm.h>
#include <sstream>

/* 
goocanvasmm质量很差，不可用
单独构建，不然会影响其他文件(包含)
g++ -g `pkg-config --cflags-only-I --libs gtkmm-3.0` `pkg-config --cflags --libs webkit2gtk-4.0` `pkg-config --cflags --libs goocanvasmm-2.0` -o bin/goocanvas1

clang++ -include mygtkmm.h -g `pkg-config --cflags-only-I --libs gtkmm-3.0` `pkg-config --cflags --libs webkit2gtk-4.0` `pkg-config --cflags --libs goocanvasmm-2.0` goocanvas1.cpp -o bin/goocanvas1
 */

class ExampleWindow : public Gtk::Window {
   public:
    ExampleWindow();

   private:
    void on_button_translate();
    void on_button_setxy();
    void on_button_scale();
    void update_label();

    Goocanvas::Canvas m_canvas;
    Glib::RefPtr<Goocanvas::Rect> m_rect;

    Gtk::Box m_box;
    Gtk::Box m_button_box;
    Gtk::Label m_label_origin, m_label_status;
    Gtk::Button m_button_translate, m_button_scale, m_button_setxy;
};
ExampleWindow::ExampleWindow()
    : m_box(Gtk::Orientation::ORIENTATION_VERTICAL, 6),
      m_button_box(Gtk::Orientation::ORIENTATION_HORIZONTAL, 6),
      m_label_origin("origin (0, 0)"),
      m_button_translate("translate(20, 20)"),
      m_button_scale("scale(1.2, 1.2)"),
      m_button_setxy("set x=50,y=50)") {
    set_title("goocanvasmm Example");

    m_box.pack_start(m_label_origin, Gtk::PackOptions::PACK_SHRINK);
    m_label_origin.set_xalign(0.0);

    m_canvas.set_size_request(640, 480);
    m_canvas.set_bounds(0, 0, 1000, 1000);

    auto root = m_canvas.get_root_item();
    m_rect = Goocanvas::Rect::create(10, 10, 60, 60);
    root->add_child(m_rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
    m_rect->property_line_width() = 10.0;
    m_rect->property_stroke_color() = "yellow";
    m_rect->property_fill_color() = "gray";
#else
    m_rect->set_property("line_width", 10.0);
    m_rect->set_property("stroke_color", Glib::ustring("yellow"));
    m_rect->set_property("fill_color", Glib::ustring("gray"));
#endif

    auto sw = Gtk::manage(new Gtk::ScrolledWindow());
    sw->add(m_canvas);
    m_box.pack_start(*sw);

    m_box.pack_start(m_button_box, Gtk::PackOptions::PACK_SHRINK);

    m_button_box.pack_start(m_button_translate, Gtk::PackOptions::PACK_SHRINK);
    m_button_translate.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_translate));

    m_button_box.pack_start(m_button_setxy, Gtk::PackOptions::PACK_SHRINK);
    m_button_setxy.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_setxy));

    m_button_box.pack_start(m_button_scale, Gtk::PackOptions::PACK_SHRINK);
    m_button_scale.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_scale));

    m_box.pack_start(m_label_status, Gtk::PackOptions::PACK_SHRINK);
    m_label_status.set_xalign(0.0);
    add(m_box);

    update_label();
}

void ExampleWindow::update_label() {
    std::stringstream str;
#ifdef GLIBMM_PROPERTIES_ENABLED
    str << "Rect: x=" << m_rect->property_x() << ", y=" << m_rect->property_y()
        << ", width=" << m_rect->property_width() << ",  height=" << m_rect->property_height()
        << ", line_width=" << m_rect->property_line_width() << std::endl;
#else
    // TODO.
#endif

    auto bounds = m_rect->get_bounds();
    str << "Item bounds: x1=" << bounds.get_x1() << ", y1=" << bounds.get_y1() << ", x2=" << bounds.get_x2()
        << ", y2=" << bounds.get_y2() << std::endl;

    m_label_status.set_text(str.str());
}

void ExampleWindow::on_button_translate() {
    m_rect->translate(20, 20);
    update_label();
}

void ExampleWindow::on_button_setxy() {
#ifdef GLIBMM_PROPERTIES_ENABLED
    m_rect->property_x() = 50;
    m_rect->property_y() = 50;
#else
    m_rect->set_property("x", 50);
    m_rect->set_property("y", 50);
#endif

    update_label();
}

void ExampleWindow::on_button_scale() {
    m_rect->scale(1.2, 1.2);
    update_label();
}

int main() {
    auto app = Gtk::Application::create();
    Goocanvas::init();

    ExampleWindow win;
    win.set_default_size(800,600);
    return app->run(win);
}
