#include <gtkmm.h>
#include <cmath>
#include <ctime>

class Clock : public Gtk::DrawingArea {
   public:
    Clock();
    virtual ~Clock();

   protected:
    // Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    bool on_timeout();

    double m_radius;
    double m_line_width;
};

Clock::Clock() : m_radius(0.42), m_line_width(0.05) {
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &Clock::on_timeout),
                                   1000);
}

Clock::~Clock() {}

bool Clock::on_draw(const Cairo::RefPtr<Cairo::Context>& context) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
    // the center of the window
    context->scale(width, height);
    context->translate(0.5, 0.5);
    context->set_line_width(m_line_width);

    context->save();
    context->set_source_rgba(0.337, 0.612, 0.117, 0.9);  // green
    context->paint();
    context->restore();
    context->arc(0, 0, m_radius, 0, 2 * M_PI);
    context->save();
    context->set_source_rgba(1.0, 1.0, 1.0, 0.8);
    context->fill_preserve();
    context->restore();
    context->stroke_preserve();
    context->clip();

    // clock ticks
    for (int i = 0; i < 12; i++) {
        double inset = 0.05;

        context->save();
        context->set_line_cap(Cairo::LINE_CAP_ROUND);

        if (i % 3 != 0) {
            inset *= 0.8;
            context->set_line_width(0.03);
        }

        context->move_to((m_radius - inset) * cos(i * M_PI / 6),
                    (m_radius - inset) * sin(i * M_PI / 6));
        context->line_to(m_radius * cos(i * M_PI / 6), m_radius * sin(i * M_PI / 6));
        context->stroke();
        context->restore(); /* stack-pen-size */
    }

    // store the current time
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);

    // compute the angles of the indicators of our clock
    double minutes = timeinfo->tm_min * M_PI / 30;
    double hours = timeinfo->tm_hour * M_PI / 6;
    double seconds = timeinfo->tm_sec * M_PI / 30;

    context->save();
    context->set_line_cap(Cairo::LINE_CAP_ROUND);

    // draw the seconds hand
    context->save();
    context->set_line_width(m_line_width / 3);
    context->set_source_rgba(0.7, 0.7, 0.7, 0.8);  // gray
    context->move_to(0, 0);
    context->line_to(sin(seconds) * (m_radius * 0.9),
                -cos(seconds) * (m_radius * 0.9));
    context->stroke();
    context->restore();

    // draw the minutes hand
    context->set_source_rgba(0.117, 0.337, 0.612, 0.9);  // blue
    context->move_to(0, 0);
    context->line_to(sin(minutes + seconds / 60) * (m_radius * 0.8),
                -cos(minutes + seconds / 60) * (m_radius * 0.8));
    context->stroke();

    // draw the hours hand
    context->set_source_rgba(0.337, 0.612, 0.117, 0.9);  // green
    context->move_to(0, 0);
    context->line_to(sin(hours + minutes / 12.0) * (m_radius * 0.5),
                -cos(hours + minutes / 12.0) * (m_radius * 0.5));
    context->stroke();
    context->restore();

    // draw a little dot in the middle
    context->arc(0, 0, m_line_width / 3.0, 0, 2 * M_PI);
    context->fill();

    return true;
}

bool Clock::on_timeout() {
    // force our program to redraw the entire clock.
    auto window = get_window();
    if (window) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                         get_allocation().get_height());
        window->invalidate_rect(r, false);
    }
    return true;
}

int main(int argc, char** argv) {
    auto app = Gtk::Application::create(argc, argv, "app_id");

    Gtk::Window window;
    window.set_title("小闹钟");
    window.set_default_size(800,800);

    Clock clock;
    window.add(clock);
    clock.show();

    return app->run(window);
}