#pragma once
#include "Bindable.h"

class HullShader:public Bindable
{
public:
	HullShader(Graphics& gfx, LPCWSTR filename);
	void Bind(Graphics& gfx) override;
private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11HullShader> pHullShader;
};