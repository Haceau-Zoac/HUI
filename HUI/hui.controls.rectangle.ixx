module;
#include <Windows.h>
#include <memory>
export module hui.controls.rectangle;
export import hui.type;
import hui.controls.control;

export namespace hui::controls
{
  class rectangle : public control
  {
  public:
    rectangle(int32 top, int32 bottom, int32 left, int32 right) noexcept
    {
      area_ = { .left = left, .top = top, .right = right, .bottom = bottom };
    }
    void draw(HDC hdc) override
    {
      Rectangle(hdc, area_.left, area_.top, area_.right, area_.bottom);
    }
  };
}