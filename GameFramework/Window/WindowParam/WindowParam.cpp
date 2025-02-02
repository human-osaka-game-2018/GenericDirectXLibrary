﻿//----------------------------------------------------------
// <filename>WindowParam.cpp</filename>
//----------------------------------------------------------

#include "WindowParam.h"

namespace gameframework
{
	RectSize WindowParam::m_windowSize = { 1280.0f, 720.0f };

	HINSTANCE WindowParam::m_hInstance = nullptr;

	HWND WindowParam::m_hWnd = nullptr;
}
