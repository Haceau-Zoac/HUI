#pragma once
#ifndef _HUI_APPLICATION_
#define _HUI_APPLICATION_
#include <Windows.h>
#include <type_traits>
#include "type.hpp"

namespace hui
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
#endif // !_HUI_APPLICATION_