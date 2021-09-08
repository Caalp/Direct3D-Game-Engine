#pragma once
#include "Bindable.h"
#include <string>

class PixelShader : public Bindable
{
public:
	PixelShader() = default;
	PixelShader(const std::string& filename);
	void Bind(Graphics& gfx);
	void Bind() override;

private:
	
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;

};