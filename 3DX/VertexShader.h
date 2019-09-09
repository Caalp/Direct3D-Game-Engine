#pragma once
#include <d3d11.h>
#include "Graphics.h"
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }
enum VS_PROP
{
	VS_2D,
	VS_3D
};
class VertexShader
{
public:
	VertexShader(VS_PROP ch,Graphics& gfx);
	~VertexShader();
	HRESULT OnRestore();
	
protected:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11Buffer* m_pcbVSMatrices;
	ID3D11Buffer* m_pcbVSMaterial;
	ID3D11Buffer* m_pcbVSLighting;
	bool m_enableLights;
	VS_PROP c;
	
};