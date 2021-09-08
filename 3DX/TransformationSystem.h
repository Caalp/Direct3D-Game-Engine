#pragma once
#include "System.h"


class TransformComponent;

class TransformationSystem : public System
{
public:
	
	TransformationSystem& GetSingleton();


	void SetTranslation(size_t id, DirectX::XMFLOAT3 t);
	void SetRotation(size_t id, DirectX::XMFLOAT3 r);
	void SetScaling(size_t id, DirectX::XMFLOAT3 s);


	void Update(float dt);

private:
	void PassDown(Scene* scene, TransformComponent& parentTransform);

};
