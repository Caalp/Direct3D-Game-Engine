#pragma once


class GraphicsResources
{

public:
	static inline GraphicsResources& GetSingleton()
	{
		static GraphicsResources gr;
		return gr;
	}



	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;


};

