module;
#include <Windows.h>
#include <type_traits>
export module hui.window;

export import hui.type;
import hui.window_class;
import hui.controls.control;

namespace hui
{
  export template <typename T>
  class window
  {
  public:
    window() noexcept : window(L"HUI") { }
    window(wchar_t const* title) noexcept
      : title_(title), window_class_(T::process) { }

    bool create() noexcept
    {
      if (created_) return false;
      window_ = CreateWindowExW(
        0,
        window_class_.class_name(),
        title_,
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        nullptr, nullptr, GetModuleHandle(nullptr), this
      );
      if (window_ != nullptr) created_ = true;
      return window_ != nullptr;
    }

    bool show() noexcept
    {
      window_class_.register_class();

      if (!created_ && !create())
        return false;

      ShowWindow(window_, SW_SHOW);
      return true;
    }

    // void add_control(controls::control* control) { children_.push_back(control); }

    virtual void on_create() { };
    virtual void on_paint(HDC hdc) { }
  protected:
    bool created_;
    window_class window_class_;
    window_handle window_;
    wchar_t const* title_;

    LRESULT handle_message(unsigned int msg, WPARAM wparam, LPARAM lparam) noexcept
    {
      switch (msg)
      {
      case WM_CREATE:
        on_create();
        break;
      case WM_PAINT:
      {
        PAINTSTRUCT ps;
        auto hdc = BeginPaint(window_, &ps);
        // for (controls::control* child : children_) if (child != nullptr) child->draw(hdc);
        on_paint(hdc);
        EndPaint(window_, &ps);
        break;
      }
      case WM_DESTROY:
        /*
        for (controls::control* child : children_)
          if (child != nullptr)
          {
            delete child;
            child = nullptr;
          }
          */
        PostQuitMessage(0);
        return 0;
      }
      return DefWindowProcW(window_, msg, wparam, lparam);
    }

    static LRESULT CALLBACK process(window_handle window, unsigned int msg, WPARAM wparam, LPARAM lparam) noexcept
    {
      T* pthis = nullptr;

      if (msg == WM_NCCREATE)
      {
        CREATESTRUCT* pcreate = reinterpret_cast<CREATESTRUCT*>(lparam);
        pthis = reinterpret_cast<T*>(pcreate->lpCreateParams);
        SetWindowLongW(window, GWLP_USERDATA, (LONG_PTR)pthis);

        pthis->window_ = window;
      }
      else
        pthis = (T*)GetWindowLongW(window, GWLP_USERDATA);

      if (pthis)
        return pthis->handle_message(msg, wparam, lparam);
      else
        return DefWindowProcW(window, msg, wparam, lparam);
    }
  };
}