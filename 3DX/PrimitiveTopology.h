#pragma once
#include "Bindable.h"

class PrimitiveTopology : public Bindable
{
public:
	PrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY P_topology);
	void Bind(Graphics& gfx) override;
private:
	D3D_PRIMITIVE_TOPOLOGY Pt;
};