#pragma once
#include "Bindables.h"

class VertexShader : public Bindables
{
public:
	VertexShader(Graphics& gfx, LPCWSTR filename, LPCSTR entryPoint, LPCSTR pModel);
	void Bind(Graphics& gfx) override;
	ID3DBlob* GetVBlob() const;

private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};