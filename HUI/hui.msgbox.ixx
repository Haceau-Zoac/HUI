module;
#include <Windows.h>
export module hui.msgbox;

export namespace hui::msgbox
{
  void info(wchar_t const* title, wchar_t const* msg) noexcept
  {
    MessageBoxW(nullptr, msg, title, MB_OK);
  }
}