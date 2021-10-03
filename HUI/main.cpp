#include "window.hpp"
#include "application.hpp"
#include "controls/rectangle.hpp"
#include "controls/color.hpp"
#include "controls/text.hpp"
#include "msgbox.hpp"

using namespace hui;
using namespace hui::controls;

class my_window : public window<my_window>
{
public:
  using hui::window<my_window>::window;
};

class my_rectangle : public rectangle
{
public:
  using rectangle::rectangle;

  void on_click(point) override { msgbox::info(L"qwq"); }
  void on_hover(point) override { set_brush(color(61, 61, 61)); }
  void on_leave() override { set_brush(color(46, 46, 46)); }
};

int main(int, wchar_t**)
{
  my_window win;
  auto rect{ new my_rectangle(20, 50, 20, 100) };
  rect->set_brush(color(46, 46, 46));
  new text(rect, L"hello");
  win.add_controls(rect);
  hui::application app{win};
  return app.exec();
}