#pragma once
#ifndef _HUI_TYPE_
#define _HUI_TYPE_
#include <Windows.h>

namespace hui
{
  using window_handle = HWND;
  using brush_handle = HBRUSH;
  using instance_handle = HINSTANCE;
  using gdi_object_handle = HGDIOBJ;

  using int8 = INT8;
  using int16 = INT16;
  using int32 = INT32;
  using int64 = INT64;

  using point = POINT;

  using rect = RECT;
}
#endif // !_HUI_TYPE_