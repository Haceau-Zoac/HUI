module;
#include <Windows.h>
export module hui.type;

export namespace hui
{
  using window_handle = HWND;
  using instance_handle = HINSTANCE;

  using int8 = INT8;
  using int16 = INT16;
  using int32 = INT32;
  using int64 = INT64;

  using rect = RECT;
}