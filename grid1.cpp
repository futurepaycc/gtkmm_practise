#include "mygtkmm.h"

class ExampleWindow : public Gtk::Window {
   public:
    ExampleWindow();
    virtual ~ExampleWindow();

   private:
    // Signal handlers:
    void on_button_quit();
    void on_button_numbered(const Glib::ustring& data);

    // Child widgets:
    Gtk::Grid m_grid;
    Gtk::Button m_button_1, m_button_2, m_button_quit;
};

ExampleWindow::ExampleWindow()
    : m_button_1("button 1"),
      m_button_2("button 2"),
      m_button_quit("Quit") {
    set_title("Gtk::Grid");

    m_grid.set_margin_start(12); //NOTE: 1, 原set_margin已没有
    // set_child(m_grid);  //NOTE: 2, 原set_child已无效
    add(m_grid); 

    m_grid.attach(m_button_1, 0, 0);
    m_grid.attach(m_button_2, 1, 0);
    m_grid.attach_next_to(m_button_quit, m_button_1, Gtk::PositionType::POS_BOTTOM, 2, 1);

    m_button_1.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), "button 1"));
    m_button_2.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), "button 2"));

    m_button_quit.signal_clicked().connect(sigc::mem_fun(*this,&ExampleWindow::on_button_quit));
}

ExampleWindow::~ExampleWindow() { //析构函数必须
}

void ExampleWindow::on_button_quit() {
    hide();
}

void ExampleWindow::on_button_numbered(const Glib::ustring& data) {
    std::cout << data << " was pressed" << std::endl;
}

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "title"); //NOTE: 这里的title似乎没啥鸟用
    ExampleWindow window;  //栈上定义window,不用delete
    window.set_default_size(600, 600);

/* 
    Gtk::Button button1("button1");
    button1.signal_clicked().connect([&]{
        using namespace std;
        cout << "别瞎按" << endl;
    }); 
    window.add(button1);
*/

    window.show_all();
    app->run(window);
    return 0;
}
