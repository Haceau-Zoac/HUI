#pragma once
#ifndef _HUI_DEVICE_CONTEXT_HPP_
#define _HUI_DEVICE_CONTEXT_HPP_
#include <Windows.h>
#include "type.hpp"
#include "controls/brush.hpp"

namespace hui
{
  using device_context_handle = HDC;
  using paint_struct = PAINTSTRUCT;
  class device_context
  {
  public:
    device_context(window_handle window)
      : window_(window) { }

    ~device_context()
    {
      ReleaseDC(window_, dc_);
    }

    void begin_paint() { dc_ = BeginPaint(window_, &ps_); }
    void end_paint() { EndPaint(window_, &ps_); }

    void draw_rectangle(rect rectangle)
    {
      Rectangle(dc_, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
    }

    void set_brush(controls::brush br)
    {
      SelectObject(dc_, static_cast<brush_handle>(br));
    }

    void repaint(rect* rectangle = nullptr)
    {
      InvalidateRect(window_, rectangle, false);
    }
  protected:
    device_context_handle dc_{ nullptr };
    window_handle window_;
    paint_struct ps_{};
  };
}
#endif // !_HUI_DEVICE_CONTEXT_HPP_