module;
#include <Windows.h>
#include <type_traits>
export module hui.application;

export import hui.type;
import hui.window;

export namespace hui
{
  template <typename W>
  class application
  {
  protected:
    W& window_;
  public:
    application(W& win) noexcept : window_(win) { }

    int exec() noexcept
    {
      window_.show();

      MSG msg;
      while (GetMessageW(&msg, nullptr, 0, 0))
      {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
      }

      return 0;
    }
  };
}
