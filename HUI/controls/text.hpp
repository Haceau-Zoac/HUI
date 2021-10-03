#pragma once
#ifndef _HUI_CONTROLS_TEXT_HPP_
#define _HUI_CONTROLS_TEXT_HPP_

#include <cwchar>
#include "../type.hpp"
#include "control.hpp"

namespace hui::controls
{
  class text : public control
  {
  public:
    text(control* parent, wchar_t const* msg)
      : text_(msg), control(parent) { }
    text(rect rectangle, wchar_t const* msg)
      : text(nullptr, msg, rectangle) { }
    text(control* parent, wchar_t const* msg, rect rectangle)
      : text_(msg), control(parent, rectangle) { }

    void set_text_color(color c)
    {
      color_ = c;
      if (dc_ != nullptr) dc_->repaint();
    }
    void set_background_mode(int mode)
    {
      background_mode_ = mode;
      if (dc_ != nullptr) dc_->repaint();
    }

    void on_paint() override
    {
      SetTextColor(dc_->dc(), color_);
      if (background_mode_ != -1) dc_->set_background_mode(background_mode_);
      TextOutW(dc_->dc(), area_.left, area_.top, text_, std::wcslen(text_));
    }

    /*
    static constexpr unsigned int format_bottom = DT_BOTTOM;
    static constexpr unsigned int format_calculate_rectangle = DT_CALCRECT;
    static constexpr unsigned int format_center = DT_CENTER;
    static constexpr unsigned int format_edit_control = DT_EDITCONTROL;
    static constexpr unsigned int format_end_ellipsis = DT_END_ELLIPSIS;
    static constexpr unsigned int format_expand_tabs = DT_EXPANDTABS;
    static constexpr unsigned int format_extern_all_eading = DT_EXTERNALLEADING;
    static constexpr unsigned int format_hide_prefix = DT_HIDEPREFIX;
    static constexpr unsigned int format_internal = DT_INTERNAL;
    static constexpr unsigned int format_left = DT_LEFT;
    static constexpr unsigned int format_modify_string = DT_MODIFYSTRING;
    static constexpr unsigned int format_no_clip = DT_NOCLIP;
    static constexpr unsigned int format_no_full_width_char_break = DT_NOFULLWIDTHCHARBREAK;
    static constexpr unsigned int format_no_prefix = DT_NOPREFIX;
    static constexpr unsigned int format_path_ellipsis = DT_PATH_ELLIPSIS;
    static constexpr unsigned int format_prefix_only = DT_PREFIXONLY;
    static constexpr unsigned int format_right = DT_RIGHT;
    static constexpr unsigned int format_right_to_left_reading = DT_RTLREADING;
    static constexpr unsigned int format_tab_stop = DT_TABSTOP;
    static constexpr unsigned int format_top = DT_TOP;
    static constexpr unsigned int format_word_break = DT_WORDBREAK;
    static constexpr unsigned int format_word_ellipsis = DT_WORD_ELLIPSIS;
    static constexpr unsigned int format_center_vertically = DT_VCENTER;
    static constexpr unsigned int format_single_line = DT_SINGLELINE;
    */
  protected:
    wchar_t const* text_;
    color color_{ 255,255,255 };
    int background_mode_{ device_context::background_mode_transparent };
  };
}

#endif // !_HUI_CONTROLS_TEXT_HPP_
