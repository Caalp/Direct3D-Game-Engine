#pragma once
#include "WinHeader.h"
#include "CustomException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <memory>


class Window
{
public:
	class Exception : public CustomException
	{
		using CustomException::CustomException;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;

	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};
private:

	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
		
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass& rhs) = delete;
		WindowClass& operator=(const WindowClass& rhs) = delete;
		static constexpr const char* d3dClassName = "d3d Engine Window";
		static WindowClass wndClass;
		
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const char* name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetWindowTitle(std::string& name);
	HWND getMainWindow() const
	{
		return hWnd;
	}
	static std::optional<int> ProcessMessages() noexcept;
	Graphics& gfx();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept;
	static LRESULT CALLBACK HandleMsgTh(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> p_gfx;
};
