module;
#include <Windows.h>
#include <memory>
export module hui.controls.control;
export import hui.type;

export namespace hui::controls
{
  class control
  {
  public:
    virtual void draw(HDC hdc) = 0;

    rect area() const noexcept { return area_; }
    void set_area(rect area) noexcept { area_ = area; }
  protected:
    rect area_;
  };
}