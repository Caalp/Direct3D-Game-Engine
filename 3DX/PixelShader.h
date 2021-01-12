#pragma once
#include "Bindable.h"
#include <string>

class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, const std::string& filename);
	void Bind(Graphics& gfx);

private:
	
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;

};