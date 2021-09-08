#pragma once

#include "RenderableComponent.h"

class ModelResource;


class ModelComponent : public RenderableComponent
{
public:


	ModelComponent(Ref<ModelResource>& modelRes);
	ModelComponent(ModelComponent&& rhs) = default;
	ModelComponent& operator=(ModelComponent&& rhs) = default;


private:

	Ref<ModelResource> m_modelResource;
};