#pragma once
#ifndef _HUI_CONTROLS_CONTROL_HPP
#define _HUI_CONTROLS_CONTROL_HPP
#include <Windows.h>
#include <memory>
#include <vector>
#include "brush.hpp"
#include "../device_context.hpp"
#include "../type.hpp"

namespace hui::controls
{
  class control
  {
  public:
    control() {}
    control(rect rectangle)
      : control(nullptr, rectangle) { }
    control(control* parent) { set_parent(parent); }
    control(control* parent, rect rectangle) : area_(rectangle) { set_parent(parent); }
    virtual ~control() {}

    void paint()
    {
      on_paint();
      for (auto&& child : children_)
        child->paint();
    }
    virtual void on_paint() = 0;

    void set_dc(device_context* dc)
    {
      dc_ = dc;
      for (auto&& child : children_)
        child->set_dc(dc);
    }

    void reset_area()
    {
      if (parent_ != nullptr)
      {
        area_.top += parent_->area_.top;
        area_.left += parent_->area_.left;
        area_.bottom += parent_->area_.bottom;
        area_.right += parent_->area_.right;
      }
    }

    void set_parent(control* parent)
    {
      parent_ = parent;
      reset_area();
      parent->add_control(this);
    }

    rect area() const noexcept { return area_; }
    void set_area(rect area) noexcept
    {
      area_ = area;
      reset_area();
      if (dc_ != nullptr) { dc_->repaint(); }
    }

    virtual void on_click(point) { }
    void hover(point pt)
    {
      if (!is_hover_)
      {
        is_hover_ = true;
        on_hover(pt);
      }
    }
    virtual void on_hover(point) { }
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
    control* parent_{ nullptr };
    rect area_{ 0,0,0,0 };
    device_context* dc_{ nullptr };
    std::vector<control*> children_;

    void add_control(control* con) { children_.push_back(con); if (dc_ != nullptr) con->set_dc(dc_); }
    template <typename Arg, typename... Args>
    void add_controls(Arg* con, Args*... cons)
    {
      add_control(con);
      if constexpr (sizeof...(cons))
        add_controls(cons);
    }
  private:
    bool is_hover_{ false };
  };
}
#endif // !_HUI_CONTROLS_CONTROL_HPP