#pragma once
#include "Bindable.h"

class GeometryShader : public Bindable
{
public:
	GeometryShader(Graphics& gfx, LPCWSTR filename);
	void Bind(Graphics& gfx) override;
	ID3DBlob* GetGSBlob() const;

private:
	Microsoft::WRL::ComPtr<ID3DBlob> pGeometryBlob;
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> pGeometryShader;
};