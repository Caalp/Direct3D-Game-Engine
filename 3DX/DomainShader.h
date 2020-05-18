#pragma once
#include "Bindable.h"

class DomainShader :public Bindable
{
public:
	DomainShader(Graphics& gfx, LPCWSTR filename);
	void Bind(Graphics& gfx) override;
private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11DomainShader> pDomainShader;
};