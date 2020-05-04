#include "Window.h"
#include <sstream>
#include "resource.h"

Window::WindowClass Window::WindowClass::wndClass;

const char * Window::WindowClass::GetName() noexcept
{
	return d3dClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}


Window::WindowClass::WindowClass() noexcept : hInst(GetModuleHandle(nullptr))

{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = static_cast<HICON>(LoadImage(
		GetInstance(), MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 32, 32, 0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(
		GetInstance(), MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wc);

	/*int scrrenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if ()
	{

	}*/
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(d3dClassName, GetInstance());
	
}

Window::Window(int width, int height,  const char* name) noexcept : width(width),
																	height(height)
																	
																	
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	// Create Window
	hWnd = CreateWindow(WindowClass::GetName(), 
						name, 
						WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 
						CW_USEDEFAULT, 
						CW_USEDEFAULT,
						wr.right - wr.left,
						wr.bottom - wr.top, 
						nullptr, 
						nullptr, 
						WindowClass::GetInstance(), this);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	p_gfx = std::make_unique<Graphics>(hWnd,width,height);
}



Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::SetWindowTitle(std::basic_string<TCHAR> title)
{
	LPCSTR a = title.c_str();
	SetWindowText(hWnd,reinterpret_cast<LPCSTR>(title.c_str()));
}

std::optional<int> Window::ProcessMessages() noexcept
{
	MSG msg;
	// while queue has messages, remove and dispatch them (but do not block on empty queue)
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		// check for quit because peekmessage does not signal this via return val
		if (msg.message == WM_QUIT)
		{
			// return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit
			return (int)msg.wParam;
		}

		// TranslateMessage will post auxilliary WM_CHAR messages from key msgs
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// return empty optional when not quitting app
	return {};
}

Graphics& Window::gfx()
{
	return *p_gfx;
}



LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
	if (msg == WM_NCCREATE) // sent WM_CREATE when a window is created
	{
		//defines initialization parameters passed to window application parameters same as CreateWindowEx
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lparam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		//Stores and sets user initialized data to window
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgTh));
		
		return pWnd->HandleMsg(hWnd, msg, wparam, lparam);
		
	}
	return DefWindowProc(hWnd, msg, wparam, lparam);
}

LRESULT WINAPI Window::HandleMsgTh(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		return pWnd->HandleMsg(hWnd, msg, wparam, lparam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KILLFOCUS:
		kbd.ClearState();
		break;
	case WM_KEYDOWN:
		// key handled except system keys
		kbd.OnKeyPressed(static_cast<unsigned char>(wparam));
		break;
		

	case WM_SYSKEYDOWN:
		if (!(lparam & 0x40000000) || kbd.AutorepeatIsEnabled()) //
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wparam));
		}
		break;
	case WM_KEYUP:
		// KeyUp event except system keys such --ALT
		kbd.OnKeyReleased(static_cast<unsigned char>(wparam));
		break;
	case WM_SYSKEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wparam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wparam));
		break;
		// Mouse move event in window message handling loop
	case WM_MOUSEMOVE:
	{
	
		const POINTS pt = MAKEPOINTS(lparam);
		// in client region -> log move, and log enter + capture mouse (if not previously in window)
		if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
		{
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		// not in client -> log move / maintain capture if button down
		else
		{
			if (wparam & (MK_LBUTTON | MK_RBUTTON)) // change those with member function
			{
				mouse.OnMouseMove(pt.x, pt.y);
			}
			// button up -> release capture / log event for leaving
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
	
		const POINTS pt = MAKEPOINTS(lparam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		
		
		const POINTS pt = MAKEPOINTS(lparam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		// stifle this mouse message if imgui wants to capture
		
		const POINTS pt = MAKEPOINTS(lparam);
		mouse.OnLeftReleased(pt.x, pt.y);
		// release mouse if outside of window
		if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		
		
		const POINTS pt = MAKEPOINTS(lparam);
		mouse.OnRightReleased(pt.x, pt.y);
		// release mouse if outside of window
		if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		
		const POINTS pt = MAKEPOINTS(lparam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wparam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}
	}
	return DefWindowProc(hWnd, msg, wparam, lparam);
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	
	// windows will allocate memory for err string and make our pointer point to it
	const DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	// 0 string length returned indicates a failure
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	// copy error string from windows-allocated buffer to std::string
	std::string errorString = pMsgBuf;
	// free windows buffer
	LocalFree(pMsgBuf);
	return errorString;
}

Window::HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	:
	Exception(line,file),
	hr(hr)
{
	
}

const char * Window::HrException::what() const noexcept
{
	std::ostringstream os;
	os << GetType() << std::endl 
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl
		<< GetOriginString();
	wBuffer = os.str();
	return wBuffer.c_str();
}

const char * Window::HrException::GetType() const noexcept
{
	return "HRESULT Window Exception";
}

HRESULT Window::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::HrException::GetErrorDescription() const noexcept
{
	return Exception::TranslateErrorCode(hr);
}

const char * Window::NoGfxException::GetType() const noexcept
{
	return "Window Exception [No Graphics]";
	
}
