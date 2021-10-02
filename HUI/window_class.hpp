#pragma once
#ifndef _HUI_WINDOW_CLASS_
#define _HUI_WINDOW_CLASS_
#include <Windows.h>
#include <functional>
#include "type.hpp"

namespace hui
{
  class window_class
  {
  public:
    using process_t = WNDPROC;
    window_class(process_t proc) noexcept : window_class(proc, L"hui") { }
    window_class(process_t proc, wchar_t const* class_name) noexcept
    {
      set_instance(GetModuleHandleW(nullptr));
      set_process(proc);
      set_class_name(class_name);
    }

    wchar_t const* class_name() const noexcept { return window_class_.lpszClassName; }
    void set_class_name(wchar_t const* class_name) noexcept { window_class_.lpszClassName = class_name; }

    instance_handle instance() const noexcept { return window_class_.hInstance; }
    void set_instance(instance_handle const instance) noexcept { window_class_.hInstance = instance; }

    void set_process(process_t proc) noexcept { window_class_.lpfnWndProc = proc; }

    void register_class() const noexcept { RegisterClassW(&window_class_); }

  protected:
    WNDCLASSW window_class_;
  };
}

#endif // !_HUI_WINDOW_CLASS_