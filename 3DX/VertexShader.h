#pragma once
#include "Bindable.h"
#include <string>

class VertexShader : public Bindable
{
public:
	VertexShader() = default;
	VertexShader(const std::string& filename);
	void Bind(Graphics& gfx) override;
	void Bind() override;
	ID3DBlob* GetVBlob() const;
	std::string  GetFilename() const;

private:
	std::string shaderFilename;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};