#pragma once
#ifndef _HUI_CONTROLS_RECTANGLE_HPP_
#define _HUI_CONTROLS_RECTANGLE_HPP_
#include <Windows.h>
#include <memory>
#include "drawable.hpp"
#include "control.hpp"
#include "../device_context.hpp"

namespace hui::controls
{
  class rectangle : public drawable
  {
  public:
    rectangle(int32 top, int32 bottom, int32 left, int32 right) noexcept
    {
      set_area({ .left = left, .top = top, .right = right, .bottom = bottom });
    }
    rectangle(control* parent, int32 top, int32 bottom, int32 left, int32 right) noexcept
      : drawable(parent)
    {
      set_area({ .left = left, .top = top, .right = right, .bottom = bottom });
    }

    void on_paint() override
    {
      if (brush_.is_valid()) dc_->set_brush(brush_);
      Rectangle(dc_->dc(), area_.left, area_.top, area_.right, area_.bottom);
    }
  };
}
#endif // !_HUI_CONTROLS_RECTANGLE_HPP_