#include "Bindables.h"

Bindables::Bindables()
{

}

Bindables::~Bindables()
{
	pVertexShader->Release();
	pPixelShader->Release();
	pBlob->Release();
	pIL->Release();
}

void Bindables::Init()
{

}
