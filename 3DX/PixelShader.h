#pragma once
#include "Bindables.h"

class PixelShader : public Bindables
{
public:
	PixelShader(Graphics& gfx,LPCWSTR filename);
	void Bind(Graphics& gfx);

private:
	
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;

};