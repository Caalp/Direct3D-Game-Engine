#pragma once
#include <d3d11.h>
#include<memory>
#include<wrl.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include "Command.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib,"DirectXTK/x86/DirectXTK.lib")

#define SHADER_DIRECTORY "../Shaders/"

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
	void BeginFrame();

	void EnableImgui();
	void DisableImgui();
	void DrawIndexed(UINT count, uint32_t startIndexLocation = 0u, int startVertexLocation = 0);
	void Draw(UINT vertexCount, UINT vertexStartLocation);
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
	bool imguiEnabled = true;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX camera;
	DirectX::XMFLOAT3 cameraPos;
	
private:
	static Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	static Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;
	std::shared_ptr<RenderTarget> pTarget;
	

	
};

