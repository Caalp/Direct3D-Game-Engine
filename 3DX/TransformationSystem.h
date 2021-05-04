#pragma once
#include "System.h"

class TransformationSystem : public System
{
public:
	
	TransformationSystem& GetSingleton();


	void SetTranslation(size_t id, DirectX::XMFLOAT3 t);
	void SetRotation(size_t id, DirectX::XMFLOAT3 r);
	void SetScaling(size_t id, DirectX::XMFLOAT3 s);


	void Update(Graphics& gfx,float dt);



};
