#pragma once
#include "Bindable.h"
#include <string>

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, const std::string& filename);
	void Bind(Graphics& gfx) override;
	ID3DBlob* GetVBlob() const;
	std::string  GetFilename() const;

private:
	std::string shaderFilename;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};