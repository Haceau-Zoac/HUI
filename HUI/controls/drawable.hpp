#pragma once
#ifndef _HUI_CONTROLS_DRAWABLE_HPP_
#define _HUI_CONTROLS_DRAWABLE_HPP_

#include "control.hpp"
#include "brush.hpp"

namespace hui::controls
{
  class drawable : public control
  {
  public:
    using control::control;
    void set_brush(brush br) { brush_ = br; if (dc_ != nullptr) dc_->repaint(); }
  protected:
    brush brush_{ nullptr };
  };
}

#endif // !_HUI_CONTROLS_DRAWABLE_HPP_