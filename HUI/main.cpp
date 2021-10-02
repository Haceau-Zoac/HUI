#include "window.hpp"
#include "application.hpp"
#include "controls/rectangle.hpp"

class my_window : public hui::window<my_window>
{
public:
  using hui::window<my_window>::window;
};

class my_rectangle : public hui::controls::rectangle
{
public:
  using hui::controls::rectangle::rectangle;

  void on_hover(int, int) override { set_brush(hui::controls::brush::black()); }

  void on_leave() override { set_brush(hui::controls::brush::white()); }
};

int main(int, wchar_t**)
{
  my_window win;
  auto rect{ new my_rectangle(0, 100, 0, 100) };
  win.add_control(rect);
  hui::application app{win};
  return app.exec();
}