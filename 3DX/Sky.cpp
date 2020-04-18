#include "Sky.h"

Sky::Sky(Graphics & gfx, const char * filePath, float skyRadius)
{

}

void Sky::Update(float ft)
{
}

DirectX::XMMATRIX Sky::GetTransformation() const
{
	return DirectX::XMMatrixIdentity();
}
