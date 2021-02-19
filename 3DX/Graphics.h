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
class ShaderViewRenderTarget;
class Graphics
{
	friend class Bindable;

public:
	Graphics(HWND hWnd,uint32_t w,uint32_t h);
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
	bool IsImguiEnabled() const;
	DirectX::XMMATRIX GetView() const;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	void SetView(DirectX::FXMMATRIX view);
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX camera);
	DirectX::XMMATRIX GetCamera() const;
	void SetCameraPos(const DirectX::XMFLOAT3& pos);
	DirectX::XMFLOAT3 GetCameraPos() const;
	void CreateViewport(float w, float h, float maxDepth=1.0f, float minDepth= 0.0f, float leftX = 0.0f, float leftY = 0.0f);

	// These functions need definition
	const UINT& GetWidth() const;
	const UINT& GetHeight() const;



private:
	uint32_t width;
	uint32_t height;
	bool imguiEnabled = true;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX camera;
	DirectX::XMFLOAT3 cameraPos;
public:
	int i = 0;
	static Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	static Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;
	Microsoft::WRL::ComPtr <ID3D11Debug> debug;
	std::shared_ptr<RenderTarget> pTarget;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	ShaderViewRenderTarget* shaderResourceViewRT;
	

	
};

