#pragma once
#ifndef _HUI_CONTROLS_BRUSH_HPP_
#define _HUI_CONTROLS_BRUSH_HPP_
#include <Windows.h>
#include "../type.hpp"
#include "color.hpp"

namespace hui::controls
{
  using brush_handle = HBRUSH;
  using color_reference = COLORREF;

  class brush
  {
  public:
    enum class type
    {
      solid
    };

    brush() noexcept { }
    brush(gdi_object_handle gdi_object) noexcept
      : brush_(static_cast<brush_handle>(gdi_object)) { }
    brush(type brush_type, color c)
    {
      switch (brush_type)
      {
      case type::solid:
        brush_ = CreateSolidBrush(c);
        break;
      }
    }

    bool is_valid() const noexcept { return brush_ != nullptr; }

    operator brush_handle() const noexcept { return brush_; }

    static brush black()  noexcept { return brush(GetStockObject(BLACK_BRUSH));  }
    static brush white()  noexcept { return brush(GetStockObject(WHITE_BRUSH));  }
    static brush gray()   noexcept { return brush(GetStockObject(GRAY_BRUSH));   }
    static brush dkgray() noexcept { return brush(GetStockObject(DKGRAY_BRUSH)); }
    static brush ltgray() noexcept { return brush(GetStockObject(LTGRAY_BRUSH)); }
    static brush dc()     noexcept { return brush(GetStockObject(DC_BRUSH));     }
    static brush hollow() noexcept { return brush(GetStockObject(HOLLOW_BRUSH)); }
    static brush null()   noexcept { return brush(GetStockObject(NULL_BRUSH));   }

  protected:
    brush_handle brush_{ nullptr };
  };
}
#endif // !_HUI_CONTROLS_BRUSH_HPP_