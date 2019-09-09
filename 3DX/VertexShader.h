#pragma once
#include <d3d11.h>
#include "Graphics.h"
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

namespace wrl = Microsoft::WRL;

class VertexShader
{
public:
	
	VertexShader();
	~VertexShader();
	HRESULT InitVS();
	
protected:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11Buffer* m_pcbVSMatrices;
	ID3D11Buffer* m_pcbVSMaterial;
	ID3D11Buffer* m_pcbVSLighting;
	bool m_enableLights;
	
	
};