#pragma once
#include <d3d11.h>
#include<memory>
#include<wrl.h>
#include <directxmath.h>
#include <d3dcompiler.h>



class Graphics
{
	friend class Bindable;
public:
	Graphics(HWND hWnd,int width,int height, bool Enable4xMsaa = false);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	HRESULT CompileShader(LPCWSTR pScrData,LPCSTR szentryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut);
	/*void DrawTestTriangle();
	void DrawCube(float angle, float x, float y);*/
	void DrawIndexed(UINT count);
	void DrawVertexed(UINT vertexCount, UINT startVertexLocation);
	void EndFrame();
	void ClearFrame(float red,float gren,float blue);
	void ResetRS();
	void ResetDSS();
	void ResetBlendState();
	void ResetGS();
	void BuildDynamicCubeMapViews(int i);
	void SetDefaultViewport();
	void SetDefaultRenderTarget();
	void GenerateMIPsCubeMap();
	//friend class Box;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetCubeMapSRV();
	DirectX::XMMATRIX GetView() const;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	void SetView(DirectX::FXMMATRIX view);
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX camera);
	DirectX::XMMATRIX GetCamera() const;
	void SetCameraPos(const DirectX::XMFLOAT3& pos);
	DirectX::XMFLOAT3 GetCameraPos() const;
private:
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX camera;
	DirectX::XMFLOAT3 cameraPos;
	int width;
	int height;
	
	//---------------------------//
	UINT m4xMsaaQuality;
protected:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pDynamicCubeMapRTV[6];
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pdsView;
	//Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
	bool init = false;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	
};