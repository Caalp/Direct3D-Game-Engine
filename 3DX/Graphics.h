#pragma once
#include <d3d11.h>
#include<memory>
#include<wrl.h>
#include <directxmath.h>
#include <d3dcompiler.h>



class Graphics
{
	friend class Bindables;
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	HRESULT CompileShader(LPCWSTR pScrData,LPCSTR szentryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut);
	void DrawTestTriangle();
	void DrawCube(float angle, float x, float y);
	void DrawIndexed(UINT count);
	void EndFrame();
	void ClearFrame(float red,float gren,float blue);
	friend class Box;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
private:
	DirectX::XMMATRIX projection;
protected:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	
};