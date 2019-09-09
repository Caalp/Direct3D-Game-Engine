#pragma once
#include <d3d11.h>
#include<memory>
#include<wrl.h>
class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	HRESULT CompileShader(LPCWSTR pScrData,LPCSTR szentryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut);
	void DrawTestTriangle();
	void DrawCube(float angle, float x, float y);
	
	void EndFrame();
	void ClearFrame(float red,float gren,float blue);

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
};