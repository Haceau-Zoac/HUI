#pragma once
#ifndef _HUI_CONTROLS_CONTROL_HPP
#define _HUI_CONTROLS_CONTROL_HPP
#include <Windows.h>
#include <memory>
#include "brush.hpp"
#include "../device_context.hpp"
#include "../type.hpp"

namespace hui::controls
{
  class control
  {
  public:
    virtual ~control() {}

    virtual void draw() = 0;

    void set_dc(device_context* dc) { dc_ = dc; }

    rect area() const noexcept { return area_; }
    void set_area(rect area) noexcept
    {
      area_ = area;
      if (dc_ != nullptr) { dc_->repaint(); };
    }

    brush get_brush() const noexcept { return brush_; }
    void set_brush(brush b) noexcept
    {
      brush_ = b;
      if (dc_ != nullptr) { dc_->repaint(); };
    }

    void hover(int x, int y)
    {
      if (!is_hover_)
      {
        is_hover_ = true;
        on_hover(x, y);
      }
    }
    virtual void on_hover([[maybe_unused]] int x, [[maybe_unused]] int y) { }
    void leave()
    {
      if (is_hover_)
      {
        is_hover_ = false;
        on_leave();
      }
    }
    virtual void on_leave() { }
  protected:
    rect area_{ 0,0,0,0 };
    brush brush_{ nullptr };
    device_context* dc_{ nullptr };
  private:
    bool is_hover_{ false };
  };
}
#endif // !_HUI_CONTROLS_CONTROL_HPP