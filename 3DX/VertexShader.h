#pragma once
#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, LPCWSTR filename);
	void Bind(Graphics& gfx) override;
	ID3DBlob* GetVBlob() const;

private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};