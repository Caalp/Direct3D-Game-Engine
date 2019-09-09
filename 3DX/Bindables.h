#pragma once
#include "Graphics.h"
#include <directxmath.h>
//#include <d3d11.h>

//#pragma comment(lib,"d3d11.lib")

namespace wrl = Microsoft::WRL;
class Bindables
{

	Bindables();
	virtual ~Bindables();
	void Init();
	virtual void Render() = 0;



protected:
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3D10PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11InputLayout> pIL;
	
	
};