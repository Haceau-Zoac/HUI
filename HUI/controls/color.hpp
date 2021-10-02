#pragma once
#ifndef _HUI_CONTROLS_COLOR_HPP_
#define _HUI_CONTROLS_COLOR_HPP_
#include <Windows.h>

namespace hui
{
  using color_reference = COLORREF;
  class color
  {
  public:
    color(int r, int g, int b)
      : color_(RGB(r, g, b)) { }

    operator color_reference() { return color_; }
  protected:
    color_reference color_;
  };
}
#endif // !_HUI_CONTROLS_COLOR_HPP_