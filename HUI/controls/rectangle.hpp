#pragma once
#ifndef _HUI_CONTROLS_RECTANGLE_HPP_
#define _HUI_CONTROLS_RECTANGLE_HPP_
#include <Windows.h>
#include <memory>
#include "control.hpp"
#include "../device_context.hpp"

namespace hui::controls
{
  class rectangle : public control
  {
  public:
    rectangle(int32 top, int32 bottom, int32 left, int32 right) noexcept
    {
      area_ = { .left = left, .top = top, .right = right, .bottom = bottom };
    }

    void draw() override
    {
      if (brush_.is_valid())
        dc_->set_brush(brush_);
      dc_->draw_rectangle(area_);
    }
  };
}
#endif // !_HUI_CONTROLS_RECTANGLE_HPP_