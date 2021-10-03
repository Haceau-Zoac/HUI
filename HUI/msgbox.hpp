#pragma once
#ifndef _HUI_MSGBOX_HPP_
#define _HUI_MSGBOX_HPP_

#include <Windows.h>

namespace hui::msgbox
{
  constexpr int ok = MB_OK;

  void info(wchar_t const* text, wchar_t const* title = L"Info", int const type = ok)
  {
    MessageBoxW(nullptr, text, title, type);
  }
}
#endif // !_HUI_MSGBOX_HPP_
