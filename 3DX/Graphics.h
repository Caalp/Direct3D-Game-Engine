#pragma once
#include <d3d11.h>
#include<memory>
#include<wrl.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include "Command.h"
#include "Imgui\\imgui_impl_dx11.h"
#include "Imgui\\imgui.h"
#include "Imgui\\imgui_impl_win32.h"


bool show_demo_window = false;
class RenderTarget;
class Graphics
{
	friend class Bindable;
	friend class Command;
public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	HRESULT CompileShader(LPCWSTR pScrData,LPCSTR szentryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut);
	void DrawTestTriangle();
	void DrawCube(float angle, float x, float y);
	void DrawIndexed(UINT count);
	void EndFrame();
	void ClearFrame(float red,float gren,float blue);
	std::shared_ptr<RenderTarget> GetTarget();
	//friend class Box;

	DirectX::XMMATRIX GetView() const;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	void SetView(DirectX::FXMMATRIX view);
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX camera);
	DirectX::XMMATRIX GetCamera() const;
	void SetCameraPos(const DirectX::XMFLOAT3& pos);
	DirectX::XMFLOAT3 GetCameraPos() const;


	// These functions need definition
	const UINT& GetWidth() const;
	const UINT& GetHeight() const;


private:
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX camera;
	DirectX::XMFLOAT3 cameraPos;
	
public:
	static Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	static Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;
	std::shared_ptr<RenderTarget> pTarget;
	

	
};

Microsoft::WRL::ComPtr<ID3D11Device> Graphics::pDevice;
Microsoft::WRL::ComPtr<IDXGISwapChain> Graphics::pSwapChain;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Graphics::pImmediateContext;