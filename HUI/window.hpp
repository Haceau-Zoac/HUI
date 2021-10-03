#pragma once
#ifndef _HUI_WINDOW_HPP_
#define _HUI_WINDOW_HPP_

#include <type_traits>
#include <vector>
#include <Windows.h>
#include <Windowsx.h>
#include "controls/control.hpp"
#include "type.hpp"
#include "window_class.hpp"
#include "device_context.hpp"

#define main __entrypoint(int argc, wchar_t* argv[]);                             \
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {    \
  int arg_count{ 0 };                                                             \
  wchar_t** arg_list{ CommandLineToArgvW(GetCommandLineW(), &arg_count) };        \
  int ret = __entrypoint(arg_count, arg_list);                                    \
  if (arg_list != nullptr)                                                        \
    LocalFree(arg_list);                                                          \
  return ret;                                                                     \
}                                                                                 \
int __entrypoint
namespace hui
{
  template <typename T>
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
      if (window_ == nullptr) return false;
      created_ = true;
      dc_ = device_context(window_);
      return true;
    }

    bool show() noexcept
    {
      window_class_.register_class();

      if (!created_ && !create())
        return false;

      ShowWindow(window_, SW_SHOW);
      return true;
    }

    void add_control(controls::control* control) { children_.push_back(control); control->set_dc(&dc_); }
    template <typename Arg, typename... Args>
    void add_controls(Arg* control, Args*... controls)
    {
      add_control(control);
      if constexpr (sizeof...(controls) > 0)
        add_controls(controls...);
    }

    virtual void on_create() { };
    virtual void on_paint([[maybe_unused]] device_context& dc) { }
  protected:
    bool created_{ false };
    window_class window_class_;
    window_handle window_{ nullptr };
    wchar_t const* title_;
    std::vector<controls::control*> children_;
    device_context dc_{ nullptr };

    void paint()
    {
      dc_.begin_paint();
      for (auto iter = children_.begin(); iter != children_.end(); ++iter)
      {
        if (*iter != nullptr) (*iter)->paint();
        else children_.erase(iter);
      }
      on_paint(dc_);
      dc_.end_paint();
    }

    void destory()
    {
      for (controls::control* child : children_)
        if (child != nullptr)
        {
          delete child;
          child = nullptr;
        }
      PostQuitMessage(0);
    }

    point mouse_position(LPARAM lparam)
    {
      int x = GET_X_LPARAM(lparam);
      int y = GET_Y_LPARAM(lparam);
      return {x, y};
    }

    bool point_in_rect(point pt, rect r)
    {
      return r.left < pt.x
        && r.right  > pt.x
        && r.top < pt.y
        && r.bottom > pt.y;
    }

    void lbuttondown(LPARAM lparam)
    {
      point pt = mouse_position(lparam);
      for (auto&& child : children_)
      {
        if (point_in_rect(pt, child->area()))
        {
          child->on_click(pt);
          break;
        }
      }
    }

    void mousemove(LPARAM lparam)
    {
      point pt = mouse_position(lparam);
      for (auto&& child : children_)
        if (point_in_rect(pt, child->area()))
          child->hover(pt);
        else
          child->leave();
    }

    LRESULT handle_message(unsigned int msg, WPARAM wparam, LPARAM lparam) noexcept
    {
      switch (msg)
      {
      case WM_CREATE:
        on_create();
        break;
      case WM_PAINT:
        paint();
        break;
      case WM_LBUTTONDOWN:
        lbuttondown(lparam);
        break;
      case WM_MOUSEMOVE:
        mousemove(lparam);
        break;
      case WM_DESTROY:
        destory();
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
#endif // !_HUI_WINDOW_HPP_